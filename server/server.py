from multiprocessing import Process
from typing import Dict, Tuple
import socket
import random
import json
import socket
import select
import time
import requests

ACTIVE_PORTS = set()
PORT_RANGE = [8081, 8099]

HOST = socket.gethostbyaddr("172.31.14.233")[0]
HOST_PORT = 8080
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
sock.bind((HOST, HOST_PORT))
sock.listen(5)

RUNNING = True


def play(conns: Dict[str, socket.socket]):
    conn1, conn2 = conns.values()

    try:
        conn1.setblocking(False)
        conn2.setblocking(False)

        while True:
            ready_sockets, _, _ = select.select(conns.values(), [], [], 0.5)

            for sock in ready_sockets:
                try:
                    data = sock.recv(128)
                    print(data)
                    if not data:
                        print("Connection closed by client.")
                        return

                    target_conn = conn2 if sock is conn1 else conn1
                    target_conn.send(data)

                except socket.error as e:
                    print(f"Play:\t\tSocket error: {e}")
                    raise e
    except Exception as e:
        print("Play:\t\tError:", e)
    finally:
        conn1.close()
        conn2.close()
        print("Connections closed.")


def match(player1_id: str, player2_id: str, port: int):
    RUNNING = True
    print(
        f"Match Server:\tCreating server for: {player1_id} vs {player2_id} on port {port}"
    )
    play_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    play_sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    play_sock.bind((HOST, port))
    play_sock.listen(2)
    conns = {}
    start_time = time.time()

    try:
        play_sock.setblocking(False)
        while len(conns) < 2 and RUNNING:
            conn, addr = play_sock.accept()
            print("\nMatch Server:\tConnected:", addr)
            data = conn.recv(2048).decode().strip("\0")
            print("Match Server:\tRecv Data:\n", data)

            if data == player1_id and "player1_id" not in conns:
                conns["player1_id"] = conn
                print(f"Match Server:\tPlayer1 {player1_id} connected on port {port}")
            elif data == player2_id and "player2_id" not in conns:
                conns["player2_id"] = conn
                print(f"Match Server:\tPlayer2 {player2_id} connected on port {port}")
            else:
                print("Match Server:\tInvalid IDs received, closing connection")
                conn.send()
                conn.close()
                continue
            if time.time() - start_time >= 15:
                RUNNING = False

        if RUNNING:
            print("Match Server:\tSending start to both clients")
            for _, conn in conns.items():
                conn.send(b"START\0")
            print("Match Server:\tConnections:", conns)
            print(
                f"Match Server:\tMatch started between {player1_id} and {player2_id} on port {port}"
            )

            play(conns)
            print(f"Match Server:\tMatch ended for {player1_id} vs {player2_id}")

    except Exception as e:
        print("Match Server:\tException in match handler:", e)

    finally:
        play_sock.close()
        ACTIVE_PORTS.discard(port)
        print(f"Match Server:\tServer on port {port} closed")

    try:
        resp = requests.post(
            "https://5rmyu3pght4flefb4djguiurq40twlwo.lambda-url.ap-south-1.on.aws/",
            json={
                "operation": "CHALLENGE_END",
                "port_id": port,
                "player1_id": player1_id,
                "player2_id": player2_id,
            },
        )

        resp.raise_for_status()
        print("Match Server:\tDeleted Entry from Match Table")
    except requests.exceptions.RequestException as e:
        print("Match Server:\tError in end:", e)


def start_match(player1_id: str, player2_id: str):
    port = random.randint(*PORT_RANGE)
    while port in ACTIVE_PORTS:
        port = random.randint(*PORT_RANGE)
    ACTIVE_PORTS.add(port)
    print("MatchMaker:\tCreating Server for:", (player1_id, player2_id), " at ", port)
    process = Process(target=match, args=(player1_id, player2_id, port))
    print("MatchMaker:\tStarting Server")
    process.start()
    print("MatchMaker:\tServer Made, Returning to main")
    return port


def main():
    global RUNNING
    print(f"Main:\t\tServer started on {HOST}:{HOST_PORT}")
    try:
        while RUNNING:
            conn, addr = sock.accept()
            print("Main:\t\t(Lambda) Connected:", addr)
            req = conn.recv(2048).decode().strip("\0")
            print("Main:\t\t(Lambda) Received request:", req)
            js = json.loads(req)

            player1_id = js["player1_id"]
            player2_id = js["player2_id"]

            port = start_match(player1_id, player2_id)
            response = json.dumps({"Port": port}).encode()
            print("Main:\t\t(Lambda) Sending Response:", response)
            conn.send(response)
            conn.close()
            print("Main:\t\t(Lambda) Disconnected")
    except Exception as e:
        print("Main:\t\tException in server:", e)
    finally:
        RUNNING = False
        sock.close()


if __name__ == "__main__":
    main()

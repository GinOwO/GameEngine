from multiprocessing import Process
import socket
import random
import json
import time


def print(*args, **kwargs):
    if kwargs.get("end", "") == "\n":
        kwargs["end"] = "\n\n"
    __builtins__.print(*args, **kwargs)


ACTIVE_PORTS = set()
PORT_RANGE = [8081, 8099]

HOST = socket.gethostbyaddr("172.31.14.233")[0]
HOST_PORT = 8080
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
sock.bind((HOST, HOST_PORT))
sock.listen(5)

processes = {}
RUNNING = True


def match(player1_id, player2_id, port, alive):
    print(
        f"Match Server:\tCreating server for: {player1_id} vs {player2_id} on port {port}"
    )
    play_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    play_sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    play_sock.bind((HOST, port))
    play_sock.listen(2)
    conns = {}

    while len(conns) < 2 and alive[0] and RUNNING:
        try:
            conn, addr = play_sock.accept()
            print("Match Server:\tConnected:", addr)
            data = conn.recv(2048).decode().strip("\0")
            js = json.loads(data)

            if js.get("player_id") == player1_id and "player1_id" not in conns:
                conns["player1_id"] = conn
                print(f"Match Server:\tPlayer1 {player1_id} connected on port {port}")
            elif js.get("player_id") == player2_id and "player2_id" not in conns:
                conns["player2_id"] = conn
                print(f"Match Server:\tPlayer2 {player2_id} connected on port {port}")
            else:
                print("Match Server:\tInvalid IDs received, closing connection")
                conn.close()
                continue

        except Exception as e:
            print("Match Server:\tException in match handler:", e)
            break

    print("Match Server:\t", conns)
    print(
        f"Match Server:\tMatch started between {player1_id} and {player2_id} on port {port}"
    )

    # Game logic could go here
    time.sleep(10)  # Simulate match duration
    print(f"Match Server:\tMatch ended for {player1_id} vs {player2_id}")

    # Clean up
    play_sock.close()
    ACTIVE_PORTS.discard(port)
    print(f"Match Server:\tServer on port {port} closed")


def start_match(player1_id, player2_id):
    port = random.randint(*PORT_RANGE)
    while port in ACTIVE_PORTS:
        port = random.randint(*PORT_RANGE)
    ACTIVE_PORTS.add(port)
    print("MatchMaker:\tCreating Match for:", (player1_id, player2_id), " at ", port)

    alive_flag = [True]
    process = Process(target=match, args=(player1_id, player2_id, port, alive_flag))
    processes[(player1_id, player2_id, port)] = (alive_flag, process)
    print("MatchMaker:\tStarting Server")
    process.start()
    print("MatchMaker:\tReturning to main")
    return port


def remove_dead_processes():
    print("Cleaner:\tStarting process cleaner")
    while RUNNING:
        time.sleep(5)  # Polling interval
        for key in list(processes.keys()):
            alive_flag, process = processes[key]
            if process.is_alive():
                continue
            else:
                del processes[key]
                print(f"Cleaner:\tCleaned up process for {key}")
    print("Cleaner:\tExiting cleaner")


def main():
    global RUNNING
    print(f"Main:\tServer started on {HOST}:{HOST_PORT}")
    Process(target=remove_dead_processes, daemon=True).start()
    try:
        while RUNNING:
            conn, addr = sock.accept()
            print("Main:\tConnected:", addr)
            req = conn.recv(2048).rstrip(b"\0").decode()
            print("Main:\tReceived request:", req)
            js = json.loads(req)

            player1_id = js["player1_id"]
            player2_id = js["player2_id"]

            port = start_match(player1_id, player2_id)
            response = json.dumps({"Port": port}).encode()
            print("Main:\tSending Response:", response)
            conn.send(response)
            conn.close()
            print("Main:\tDisconnected")
    except Exception as e:
        print("Main:\tException in server:", e)
    finally:
        RUNNING = False
        sock.close()


if __name__ == "__main__":
    main()

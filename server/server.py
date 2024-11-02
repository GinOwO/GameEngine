from multiprocessing import Process
import socket
import random
import json
import time

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
    print(f"Creating server for: {player1_id} vs {player2_id} on port {port}")
    play_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    play_sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    play_sock.bind((HOST, port))
    play_sock.listen(2)
    conns = {}

    while len(conns) < 2 and alive[0] and RUNNING:
        try:
            conn, addr = play_sock.accept()
            print("Connected:", addr)
            data = conn.recv(2048).decode().strip("\0")
            js = json.loads(data)

            if js.get("player_id") == player1_id and "player1_id" not in conns:
                conns["player1_id"] = conn
                print(f"Player1 {player1_id} connected on port {port}")
            elif js.get("player_id") == player2_id and "player2_id" not in conns:
                conns["player2_id"] = conn
                print(f"Player2 {player2_id} connected on port {port}")
            else:
                print("Invalid IDs received, closing connection")
                conn.close()
                continue

        except Exception as e:
            print("Exception in match handler:", e)
            break

    print(f"Match started between {player1_id} and {player2_id} on port {port}")

    # Game logic could go here
    time.sleep(10)  # Simulate match duration
    print(f"Match ended for {player1_id} vs {player2_id}")

    # Clean up
    play_sock.close()
    ACTIVE_PORTS.discard(port)
    print(f"Server on port {port} closed")


def start_match(player1_id, player2_id):
    port = random.randint(*PORT_RANGE)
    while port in ACTIVE_PORTS:
        port = random.randint(*PORT_RANGE)
    ACTIVE_PORTS.add(port)

    alive_flag = [True]
    process = Process(target=match, args=(player1_id, player2_id, port, alive_flag))
    processes[(player1_id, player2_id, port)] = (alive_flag, process)
    process.start()
    return port


def remove_dead_processes():
    print("Starting process cleaner")
    while RUNNING:
        time.sleep(5)  # Polling interval
        for key in list(processes.keys()):
            alive_flag, process = processes[key]
            if process.is_alive():
                continue
            else:
                del processes[key]
                print(f"Cleaned up process for {key}")
    print("Exiting cleaner")


def main():
    global RUNNING
    print(f"Server started on {HOST}:{HOST_PORT}")
    Process(target=remove_dead_processes, daemon=True).start()
    try:
        while RUNNING:
            conn, addr = sock.accept()
            print("Connected:", addr)
            req = conn.recv(2048).rstrip(b"\0").decode()
            js = json.loads(req)
            print("Received request:", json.dumps(js, indent=2))

            player1_id = js["player1_id"]
            player2_id = js["player2_id"]

            port = start_match(player1_id, player2_id)
            response = json.dumps({"Port": port}).encode()
            conn.send(response)
            conn.close()
    except Exception as e:
        print("Exception in main server:", e)
    finally:
        RUNNING = False
        sock.close()


if __name__ == "__main__":
    main()

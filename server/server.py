from multiprocessing import Process
import asyncio
import socket
import random
import json

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
    print("Creating server for:", player1_id, player2_id, "at", port)
    play_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    play_sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    play_sock.bind((HOST, port))
    play_sock.listen(2)
    conns = {}
    while len(conns) < 2 and alive[0] and RUNNING:
        conn, addr = sock.accept()
        print("Connected: ", addr)
        data = conn.recv(2048).decode().strip("\0")
        print(data)
        js = json.loads(data)
        if js.get("player_id") == player1_id and "player1_id" not in conns:
            conns["player1_id"] = conn
            print("Player1", player1_id, "connected at", port)
        elif js.get("player_id") == player2_id and "player2_id" not in conns:
            print("Player2", player2_id, "connected at", port)
            conns["player2_id"] = conn
        else:
            print("Invalid ids")
            exit(1)
    print(f"Match started for {player1_id} vs {player2_id}")
    pass
    print(f"Match ended for {player1_id} vs {player2_id}")
    print("Killing server at port: ", port)


def start_match(player1_id, player2_id):
    port = random.randint(*PORT_RANGE)
    while port in ACTIVE_PORTS:
        port = random.randint(*PORT_RANGE)
    ACTIVE_PORTS.add(port)
    processes[(player1_id, player2_id, port)] = [[True], None]
    process = Process(
        target=match,
        args=(
            player1_id,
            player2_id,
            port,
            processes[(player1_id, player2_id, port)][0],
        ),
    )
    processes[(player1_id, player2_id, port)][1] = process
    process.start()
    return port
    # with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    #     if s.connect_ex(("localhost", port)) != 0:
    #         return port


def remove_dead_processes():
    print("Starting Cleaner")
    started = set()
    while RUNNING:
        for id in processes:
            print(id)
            process = processes[id][1]
            if process is not None:
                if process.is_alive():
                    print("Adding to started: ", id)
                    started.add(id)
                elif id in started:
                    print("Deleting from started: ", id)
                    del processes[id]
                    started.remove(id)
                    break
    print("Exiting cleaner")


def main():
    print("Started Listening on ", HOST, " at ", HOST_PORT)
    Process(target=remove_dead_processes).start()
    try:
        while True:
            conn, addr = sock.accept()
            print("Connected: ", addr)
            req = conn.recv(2048).rstrip(b"\0").decode()
            js = json.loads(req)
            print(json.dumps(js, indent=2))
            port = start_match(int(js["player1_id"]), int(js["player2_id"]))
            print(port)
            conn.send(json.dumps({"Port": port}).encode())
            conn.close()
    except Exception as e:
        print("Exception in main:", e)
        RUNNING = False
        sock.close()


if __name__ == "__main__":
    main()

from multiprocessing import Process
import asyncio
import socket
import random
import requests

ACTIVE_PORTS = set()
PORT_RANGE = [8081, 8099]

HOST = socket.gethostbyaddr("172.31.14.233")[0]
HOST_PORT = 8080
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
sock.bind((HOST, HOST_PORT))
sock.listen(5)


def funcXYZ(player1_id, player2_id):
    print(f"Match started for {player1_id} vs {player2_id}")


def get_available_port():
    port = random.randint(*PORT_RANGE)
    while port in ACTIVE_PORTS:
        port = random.randint(*PORT_RANGE)
    ACTIVE_PORTS.add(port)
    return port
    # with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    #     if s.connect_ex(("localhost", port)) != 0:
    #         return port


def main():
    print("Started Listening on ", HOST, " at ", HOST_PORT)
    while True:
        conn, addr = sock.accept()
        print("Connected: ", addr)
        port = get_available_port()
        req = conn.recv()
        print(req)
        conn.send(("{" + f'"Port": "{port}"' + "}").encode())
        conn.close()


if __name__ == "__main__":
    main()

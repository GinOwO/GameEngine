import asyncio
from aiohttp import web
from multiprocessing import Process
import socket
import random

HOST = "0.0.0.0"
PORT = 8080
ACTIVE_PORTS = set()  # Tracks ports in use for matches


async def handle_challenge(request):
    """
    Handle incoming CHALLENGE requests by forking a new process for each match.
    """
    try:
        data = await request.json()
        player1_id = data.get("player1_id")
        player2_id = data.get("player2_id")

        if not player1_id or not player2_id:
            return web.json_response({"error": "Player IDs are required"}, status=400)

        # Fork a new process for handling the match
        process = Process(target=funcXYZ, args=(player1_id, player2_id))
        process.start()

        # Get an available port for the match
        match_port = get_available_port()
        ACTIVE_PORTS.add(match_port)

        # Respond with the match port for clients to connect
        return web.json_response({"portid": match_port})
    except Exception as e:
        print(f"Error handling challenge: {e}")
        return web.json_response({"error": "Internal server error"}, status=500)


def funcXYZ(player1_id, player2_id):
    """
    Placeholder function for match handling.
    This function can be implemented with actual match logic.
    """
    print(f"Match started for {player1_id} vs {player2_id}")
    # Simulate match handling; replace this with actual logic
    # This function would ideally handle player communication on the assigned port


def get_available_port():
    """
    Find an available port that is not in use.
    """
    while True:
        port = random.randint(30000, 40000)  # Assign ports in a specific range
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            if s.connect_ex(("localhost", port)) != 0:  # Port is available
                return port


async def init_app():
    """
    Initialize the aiohttp web application.
    """
    app = web.Application()
    app.router.add_post("/getPortId", handle_challenge)
    return app


def main():
    """
    Main entry point to start the async server on EC2 instance.
    """
    app = init_app()
    web.run_app(app, host=HOST, port=PORT)


if __name__ == "__main__":
    main()

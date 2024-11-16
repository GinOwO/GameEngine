import configparser
import json
import os
import random
import socket
import time
from enum import Enum

import boto3
import gymnasium
import numpy as np
from gymnasium import spaces

BUFFER_SIZE = 2048
TARGET_DISTANCE = 7.5


class Action(Enum):
    MOVE_FORWARD = 0
    MOVE_BACKWARD = 1
    MOVE_LEFT = 2
    MOVE_RIGHT = 3
    SHOOT = 4


class EnemyEnv(gymnasium.Env):
    def __init__(self, config_file, mode="range"):
        super(EnemyEnv, self).__init__()
        self.mode = mode

        self.steps = 0
        self.action_space = spaces.Discrete(5)
        self.observation_space = spaces.Box(
            low=-np.inf, high=np.inf, shape=(9,), dtype=np.float32
        )

        self.enemy_pos = np.array([0.0, 0.0, 0.0])
        self.player_pos = np.array([0.0, 0.0, 0.0])
        self.enemy_hp = 100.0
        self.player_hp = 100.0
        self.distance_to_player = 0.0
        self.shot_hit = False

        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        config = configparser.ConfigParser()
        config.add_section("Socket")
        config.set("Socket", "port", str(random.randint(16000, 63000)))
        config.write(open(config_file, "w"), False)

        self.port = int(config["Socket"]["port"])
        self.sock.bind(("localhost", self.port))
        self.sock.listen(1)
        print(f"Server listening on port {self.port}")

        pid = os.fork()
        if pid == 0:
            time.sleep(4)
            os.execv("./build/GameEngine", (r"./build/GameEngine",))

        self.conn = None

        while not self.conn:
            self.conn, addr = self.sock.accept()
            print(f"Connection from {addr}")

        self.conn.setblocking(True)

    def set_mode(self, mode):
        self.mode = mode

    def send(self, msg):
        self.conn.send(msg.encode().ljust(BUFFER_SIZE, b"\0"))

    def recv(self):
        msg = self.conn.recv(
            BUFFER_SIZE, socket.MSG_WAITALL).strip(b"\0").decode()
        return msg

    def reset(self, *_, **__):
        self.send("reset")
        state = self.recv().split(",")
        self.update_states(state)
        return self._get_obs(), {}

    def update_states(self, state):
        try:
            self.enemy_hp = float(state[0])
            self.player_hp = float(state[1])
            self.enemy_pos = np.array(
                [float(state[2]), float(state[3]), float(state[4])]
            )
            self.player_pos = np.array(
                [float(state[5]), float(state[6]), float(state[7])]
            )
            self.distance_to_player = np.linalg.norm(
                self.enemy_pos - self.player_pos)
            self.shot_hit = state[8] == "True"

        except (ValueError, IndexError) as e:
            print("Error updating states:", e)
            raise

    def _get_obs(self):
        return np.concatenate(
            [
                self.enemy_pos,
                self.player_pos,
                [
                    self.enemy_hp,
                    self.player_hp,
                    self.distance_to_player,
                ],
            ]
        )

    def step(self, action):
        done = False
        self.steps += 1
        reward = 0.0

        self.send(f"action,{action}")
        state = self.recv().split(",")
        self.update_states(state)

        print(
            action,
            done,
            self.enemy_pos,
            self.player_pos,
            [
                self.enemy_hp,
                self.player_hp,
                self.distance_to_player,
            ],
            reward,
            end="\r",
        )

        return self._get_obs(), reward, done, {}, {}

    def close(self):
        self.conn.close()


def send_to_sagemaker(
    obs,
    region,
    access_key,
    secret_key,
):
    endpoint_name = "pytorch-inference-2024-11-14-22-14-36-087"
    payload = json.dumps({"obs": obs.tolist()})

    runtime = boto3.Session(
        aws_access_key_id=access_key,
        aws_secret_access_key=secret_key,
        region_name=region,
    ).client("sagemaker-runtime")

    response = runtime.invoke_endpoint(
        EndpointName=endpoint_name, ContentType="application/json", Body=payload
    )

    return json.loads(response["Body"].read().decode() or '{"action":0}')


if __name__ == "__main__":
    try:
        print("Attempting build")
        os.system("cmake --build build")
        os.system("cp ./build/GameEngine ./AI/GameEngine")
    except:
        pass
    os.system("clear")
    env = EnemyEnv("config.conf")

    # Train and save models as needed
    # face_model = train_behavior(env, "face", 25000)
    # shoot_model = PPO.load("enemy_rl_turn_model", env=env)
    # range_model = train_behavior(env, "range", 25000 , model=range_model)
    # range_model = PPO.load("enemy_rl_range_model", env=env)
    # shoot_model = train_behavior(env, "shoot", 7500, model=range_model)
    # shoot_model = PPO.load("enemy_rl_shoot_model", env=env)
    # final_model = train_behavior(env, "final", 17500, model=range_model)

    done = False
    obs, _ = env.reset()
    env.set_mode("final")

    while not done:
        action = send_to_sagemaker(obs, input(), input(), input())["action"]
        action = int(action)
        obs, reward, done, info, _ = env.step(action)
    print("\nAI Done")
    env.close()

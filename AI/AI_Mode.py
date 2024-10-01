import gymnasium
import numpy as np
import socket
import configparser
import random
import os

from enum import Enum
from gymnasium import spaces
from stable_baselines3 import PPO


class Action(Enum):
    MOVE_FORWARD = 0
    MOVE_BACKWARD = 1
    MOVE_LEFT = 2
    MOVE_RIGHT = 3
    JUMP = 4
    ROTATE_LEFT = 5
    ROTATE_RIGHT = 6
    SHOOT = 7


class EnemyEnv(gymnasium.Env):
    def __init__(self, config_file):
        super(EnemyEnv, self).__init__()

        self.steps = 0
        self.action_space = spaces.Discrete(8)
        self.observation_space = spaces.Box(
            low=-np.inf, high=np.inf, shape=(10,), dtype=np.float32
        )

        self.enemy_pos = np.array([0.0, 0.0, 0.0])
        self.player_pos = np.array([0.0, 0.0, 0.0])
        self.enemy_hp = 100.0
        self.player_hp = 100.0
        self.distance_to_player = 0.0
        self.shot_hit = False
        self.angle_diff = 0.0

        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        config = configparser.ConfigParser()
        config.add_section("Socket")
        config.set("Socket", "port", str(random.randint(16000, 63000)))
        config.write(open(config_file, "w"), False)

        self.port = int(config["Socket"]["port"])
        self.sock.bind(("localhost", self.port))
        self.sock.listen(1)
        print(f"Server listening on port {self.port}")

        id = os.fork()
        if id == 0:
            os.execv("./AI/GameEngine", (r"./AI/GameEngine",))
        else:
            self.conn = None

            while not self.conn:
                self.conn, addr = self.sock.accept()
                print(f"Connection from {addr}")

            self.conn.setblocking(True)

    def reset(self, *_, **__):
        self.conn.send(b"reset")
        state = self.conn.recv(1024).decode().split(",")
        print("Recv State:\t", state)

        self.enemy_hp = float(state[0])
        self.player_hp = float(state[1])
        self.enemy_pos = np.array([float(state[2]), float(state[3]), float(state[4])])
        self.player_pos = np.array([float(state[5]), float(state[6]), float(state[7])])
        self.distance_to_player = np.linalg.norm(self.enemy_pos - self.player_pos)
        self.angle_diff = 180.0

        return self._get_obs(), {}

    def _get_obs(self):
        return np.concatenate(
            [
                self.enemy_pos,
                self.player_pos,
                [
                    self.enemy_hp,
                    self.player_hp,
                    self.distance_to_player,
                    self.angle_diff,
                ],
            ]
        )

    def __calculate_angle(self, pos1, pos2):
        return np.arctan2(pos2[1] - pos1[1], pos2[0] - pos1[0])

    def step(self, action):
        print(self.steps)
        self.steps += 1
        reward = 0.0

        print("Send ACTION:\t", action)
        self.conn.send(f"action,{action}".encode())
        state = self.conn.recv(1024).decode().split(",")
        print("Recv State:\t", state)

        self.enemy_pos = np.array([float(state[0]), float(state[1]), float(state[2])])
        self.player_pos = np.array([float(state[3]), float(state[4]), float(state[5])])
        self.enemy_hp = float(state[6])
        self.player_hp = float(state[7])
        self.shot_hit = state[8] == "True"
        self.distance_to_player = np.linalg.norm(self.enemy_pos - self.player_pos)

        player_angle = self.__calculate_angle(self.player_pos, self.enemy_pos)
        enemy_facing_angle = self.__calculate_angle(self.enemy_pos, self.player_pos)

        self.angle_diff = abs(player_angle - enemy_facing_angle)

        if self.angle_diff < np.pi / 32:
            reward += 10
        else:
            reward -= 12
        if self.shot_hit:
            reward += 20
        if self.distance_to_player > 20.0:
            reward -= 4
        else:
            reward += 3
        if action == Action.JUMP:
            reward -= 3

        print(
            self.enemy_pos,
            self.player_pos,
            [self.enemy_hp, self.player_hp, self.distance_to_player, self.angle_diff],
            reward,
        )
        return (
            self._get_obs(),
            reward,
            self.enemy_hp <= 0 or self.player_hp <= 0,
            {},
            {},
        )

    def close(self):
        self.conn.close()


if __name__ == "__main__":
    os.system("clear")
    env = EnemyEnv("config.conf")

    model = PPO("MlpPolicy", env, verbose=1)
    model.learn(total_timesteps=10000)
    model.save("enemy_rl_model")

    obs, _ = env.reset()
    done = False
    while not done:
        action, _states = model.predict(obs)
        obs, reward, done, info, _ = env.step(action)

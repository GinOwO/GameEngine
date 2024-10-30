import gymnasium
import numpy as np
import socket
import configparser
import random
import os
import time

from enum import Enum
from gymnasium import spaces
from stable_baselines3 import PPO

BUFFER_SIZE = 2048


def calculate_angle(pos1, pos2):
    return np.arctan2(pos2[1] - pos1[1], pos2[0] - pos1[0])


def quaternion_to_yaw(quaternion):
    w, x, y, z = quaternion
    siny_cosp = 2 * (w * z + x * y)
    cosy_cosp = 1 - 2 * (y * y + z * z)
    yaw = np.arctan2(siny_cosp, cosy_cosp)
    return yaw


class Action(Enum):
    MOVE_FORWARD = 0
    MOVE_BACKWARD = 1
    MOVE_LEFT = 2
    MOVE_RIGHT = 3
    SHOOT = 4
    ROTATE_LEFT = 5
    ROTATE_RIGHT = 6
    JUMP = 7  # Disabled for now


class EnemyEnv(gymnasium.Env):
    def __init__(self, config_file):
        super(EnemyEnv, self).__init__()

        self.steps = 0
        self.action_space = spaces.Discrete(7)
        self.observation_space = spaces.Box(
            low=-np.inf, high=np.inf, shape=(18,), dtype=np.float32
        )

        self.enemy_pos = np.array([0.0, 0.0, 0.0])
        self.player_pos = np.array([0.0, 0.0, 0.0])
        self.player_rot_quaternion = np.array([0.0, 0.0, 0.0, 0.0])
        self.player_rot_quaternion = np.array([0.0, 0.0, 0.0, 0.0])
        self.enemy_hp = 100.0
        self.player_hp = 100.0
        self.distance_to_player = 0.0
        self.shot_hit = False
        self.angle_diff = 0.0
        self.prev_hp = 0

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

    def send(self, msg):
        self.conn.send(msg.encode().ljust(BUFFER_SIZE, b"\0"))

    def recv(self):
        msg = self.conn.recv(BUFFER_SIZE, socket.MSG_WAITALL).strip(b"\0").decode()
        # self.send("ACK")
        return msg

    def reset(self, *_, **__):
        self.send("reset")
        state = self.recv().split(",")
        # print("Recv State:\t", state)

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
            self.distance_to_player = np.linalg.norm(self.enemy_pos - self.player_pos)
            self.shot_hit = state[8] == "True"
            self.enemy_rot_quaternion = np.array(
                [float(state[9]), float(state[10]), float(state[11]), float(state[12])]
            )  # w, x, y, z

            self.player_rot_quaternion = np.array(
                [float(state[13]), float(state[14]), float(state[15]), float(state[16])]
            )  # w, x, y, z

            enemy_yaw = quaternion_to_yaw(self.enemy_rot_quaternion)
            player_angle = calculate_angle(self.player_pos, self.enemy_pos)

            self.angle_diff = abs(player_angle - enemy_yaw)
            self.angle_diff = min(self.angle_diff, 2 * np.pi - self.angle_diff)
        except ValueError as e:
            print("\n\nValue Error:\n", *zip(range(len(state)), state))
            raise Exception(e)
        except IndexError as e:
            print("\n\nIndex Error:\n", *zip(range(len(state)), state))
            raise Exception(e)

    def _get_obs(self):
        return np.concatenate(
            [
                self.enemy_pos,
                self.player_pos,
                self.enemy_rot_quaternion,
                self.player_rot_quaternion,
                [
                    self.enemy_hp,
                    self.player_hp,
                    self.distance_to_player,
                    self.angle_diff,
                ],
            ]
        )

    def step(self, action):
        done = False
        self.steps += 1
        reward = 0.0

        # print("Send ACTION:\t", action)
        self.send(f"action,{action}")
        state = self.recv().split(",")
        # print("Recv State:\t", state)

        self.update_states(state)

        reward += int(max(abs(np.pi - self.angle_diff), self.angle_diff) / np.pi * 30)

        if self.shot_hit:
            reward += 50

        if self.distance_to_player > 20.0:
            reward -= 20

        # if action == Action.JUMP:
        #     reward -= 10
        if action == Action.SHOOT:
            reward += 5
            if self.shot_hit:
                reward += 15
        else:
            reward += 6
            if action in (Action.MOVE_LEFT, Action.MOVE_RIGHT):
                reward += 14

        if self.enemy_hp < self.prev_hp:
            reward -= 20
            self.prev_hp = self.enemy_hp

        done = self.enemy_hp <= 0 or self.player_hp <= 0

        print(
            action,
            done,
            self.enemy_pos,
            self.player_pos,
            [
                self.enemy_hp,
                self.player_hp,
                self.distance_to_player,
                self.angle_diff,
            ],
            reward,
            end="\r",
        )

        # if done:
        #     self.reset()

        return self._get_obs(), reward, done, {}, {}

    def close(self):
        self.conn.close()


if __name__ == "__main__":
    try:
        print("Attempting build")
        os.system("cmake --build build")
        os.system("cp ./build/GameEngine ./AI/GameEngine")
    except:
        pass
    os.system("clear")
    env = EnemyEnv("config.conf")

    model = PPO("MlpPolicy", env, verbose=1, learning_rate=7.5e-4)
    model.learn(total_timesteps=500000)
    model.save(f"enemy_rl_model_{time.time()}")
    print("\n\nTraining Done\n\n")

    obs, _ = env.reset()
    done = False
    while not done:
        action, _ = model.predict(obs)
        obs, reward, done, info, _ = env.step(action)
    print("Done")

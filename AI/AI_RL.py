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
TARGET_DISTANCE = 7.5


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
    JUMP = 5
    ROTATE_LEFT = 6
    ROTATE_RIGHT = 7


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
        # self.player_rot_quaternion = np.array([0.0, 0.0, 0.0, 0.0])
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
        msg = self.conn.recv(BUFFER_SIZE, socket.MSG_WAITALL).strip(b"\0").decode()
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
            self.distance_to_player = np.linalg.norm(self.enemy_pos - self.player_pos)
            self.shot_hit = state[8] == "True"
            self.enemy_rot_quaternion = np.array(
                [float(state[9]), float(state[10]), float(state[11]), float(state[12])]
            )
            self.action_space = spaces.Discrete(5)
            self.player_rot_quaternion = np.array(
                [float(state[13]), float(state[14]), float(state[15]), float(state[16])]
            )

            enemy_yaw = quaternion_to_yaw(self.enemy_rot_quaternion)
            player_angle = calculate_angle(self.player_pos, self.enemy_pos)
            self.angle_diff = abs(player_angle - enemy_yaw)
            self.angle_diff = min(self.angle_diff, 2 * np.pi - self.angle_diff)
        except (ValueError, IndexError) as e:
            print("Error updating states:", e)
            raise

    def _get_obs(self):
        return np.concatenate(
            [
                self.enemy_pos,
                self.player_pos,
                # self.enemy_rot_quaternion,
                # self.player_rot_quaternion,
                [
                    self.enemy_hp,
                    self.player_hp,
                    self.distance_to_player,
                    # self.angle_diff,
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

        if self.enemy_hp <= 0 or self.player_hp <= 0:
            done = True
            reward = 100 if self.enemy_hp > 0 else -100

        if not done:
            if self.mode == "range":
                reward = -abs(TARGET_DISTANCE - self.distance_to_player)
            elif self.mode == "face":
                reward = -self.angle_diff
            elif self.mode == "shoot":
                reward = 10.0 if self.shot_hit else (5.0 if action == 4 else -2.5)
            elif self.mode == "final":
                reward = (
                    10.0 if self.shot_hit else (5.0 if action == 4 else -2.5)
                ) - abs(TARGET_DISTANCE - self.distance_to_player)

        print(
            action,
            done,
            self.enemy_pos,
            self.player_pos,
            [
                self.enemy_hp,
                self.player_hp,
                self.distance_to_player,
                # self.angle_diff,
            ],
            reward,
            end="\r",
        )

        return self._get_obs(), reward, done, {}, {}

    def close(self):
        self.conn.close()


def train_behavior(env, mode, timesteps, model=None):
    env.set_mode(mode)
    if model is None:
        model = PPO("MlpPolicy", env, verbose=1, learning_rate=0.001)
    model.learn(total_timesteps=timesteps)
    model.save(f"enemy_rl_{mode}_model_{time.time()}")
    print(f"\nTraining for {mode} behavior complete\n")
    return model


if __name__ == "__main__":
    try:
        print("Attempting build")
        os.system("cmake --build build")
        os.system("cp ./build/GameEngine ./AI/GameEngine")
    except:
        pass
    os.system("clear")
    env = EnemyEnv("config.conf")

    env.action_space = spaces.Discrete(8)
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
    final_model = PPO.load("enemy_rl_final_model", env=env)
    while not done:
        action, _ = final_model.predict(obs)
        obs, reward, done, info, _ = env.step(action)
    print("Testing Done")
    env.close()

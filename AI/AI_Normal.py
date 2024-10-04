import numpy as np
import socket
import configparser
import random
import os
import time

from enum import Enum

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


class EnemyEnv:
    def __init__(self, config_file):
        self.steps = 0
        self.enemy_pos = np.array([0.0, 0.0, 0.0])
        self.player_pos = np.array([0.0, 0.0, 0.0])
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
            time.sleep(3)
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
        return msg

    def reset(self, *_, **__):
        self.send("reset")
        state = self.recv().split(",")

        self.update_states(state)

        return self._get_obs()

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

            self.player_rot_quaternion = np.array(
                [float(state[13]), float(state[14]), float(state[15]), float(state[16])]
            )

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

    def step(self):
        done = False
        self.steps += 1

        enemy_yaw = quaternion_to_yaw(self.enemy_rot_quaternion)
        player_angle = calculate_angle(self.player_pos, self.enemy_pos)
        self.angle_diff = abs(player_angle - enemy_yaw)
        self.angle_diff = min(self.angle_diff, 2 * np.pi - self.angle_diff)

        actions = [[(Action.MOVE_FORWARD, Action.MOVE_BACKWARD)[self.steps <= 20]], []][
            random.random() < 0.7
        ]
        if self.angle_diff > np.radians(12):
            if player_angle > enemy_yaw:
                actions += [Action.ROTATE_RIGHT] * 2
            else:
                actions += [Action.ROTATE_LEFT] * 2
        else:
            if self.distance_to_player > 15:
                actions += [
                    random.choice([Action.MOVE_FORWARD, Action.MOVE_BACKWARD])
                ] * 2
            else:
                actions.append(
                    random.choice(
                        [
                            Action.MOVE_LEFT,
                            Action.MOVE_RIGHT,
                            Action.MOVE_FORWARD,
                            Action.MOVE_BACKWARD,
                        ]
                    )
                )

        actions += [Action.SHOOT] * 3

        print(self.distance_to_player, actions)
        for action in actions:
            self.send(f"action,{action.value}")
        state = self.recv().split(",")

        self.update_states(state)

        done = self.enemy_hp <= 0 or self.player_hp <= 0

        return self._get_obs(), 0.0, done, {}

    def close(self):
        self.conn.close()


if __name__ == "__main__":
    os.system("cmake --build build")
    os.system("clear")
    env = EnemyEnv("config.conf")

    obs = env.reset()
    done = False
    while not done:
        obs, reward, done, info = env.step()
    print("AI finished execution.")

#pragma once

#include <string>
#include <memory>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

class SocketManager {
    public:
	SocketManager(const SocketManager &) = delete;
	SocketManager &operator=(const SocketManager &) = delete;

	static SocketManager &get_instance()
	{
		static SocketManager instance;
		return instance;
	}

	void initialize(const std::string &config_file)
	{
		int port = read_config(config_file);
		create_socket(port);
	}

	void send_data(const std::string &data)
	{
		if (sock_fd == -1) {
			throw std::runtime_error("Socket not initialized");
		}
		try {
			send(sock_fd, data.c_str(), data.size(), 0) < 0;
		} catch (std::exception) {
			std::cout << "Error\n";
		}
	}

	std::string receive_data()
	{
		if (sock_fd == -1) {
			throw std::runtime_error("Socket not initialized");
		}

		char buffer[1024] = { 0 };
		int bytes_received = recv(sock_fd, buffer, sizeof(buffer), 0);
		if (bytes_received < 0) {
			throw std::runtime_error("Failed to receive data");
		}

		return std::string(buffer, bytes_received);
	}

    private:
	int sock_fd = -1;
	sockaddr_in server_address;

	SocketManager() {};

	void create_socket(int port)
	{
		if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
			throw std::runtime_error("Socket creation error");
		}

		server_address.sin_family = AF_INET;
		server_address.sin_port = htons(port);
		server_address.sin_addr.s_addr = INADDR_ANY;

		if (connect(sock_fd, (struct sockaddr *)&server_address,
			    sizeof(server_address)) < 0) {
			throw std::runtime_error("Connection to server failed");
		}

		std::cout << "Connected to server on port " << port << '\n';
	}

	int read_config(const std::string &config_file)
	{
		std::ifstream file(config_file);
		if (!file.is_open()) {
			throw std::runtime_error("Unable to open config file");
		}

		std::string line;
		while (std::getline(file, line)) {
			std::istringstream is_line(line);
			std::string key;
			if (std::getline(is_line, key, '=')) {
				std::string value;
				if (std::getline(is_line, value) &&
				    key == "port") {
					return std::stoi(value);
				}
			}
		}

		throw std::runtime_error("Port not found in config file");
	}

	~SocketManager()
	{
		if (sock_fd != -1) {
			close(sock_fd);
		}
	}
};

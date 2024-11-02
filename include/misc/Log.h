#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <mutex>
#include <ctime>
#include <memory>

class Logger {
    public:
	enum LogLevel { DEBUG, INFO, WARNING, ERROR, FATAL };

	static Logger &get_instance()
	{
		static Logger instance;
		return instance;
	}

	void setLogLevel(LogLevel level)
	{
		log_level = level;
	}

	template <typename T> Logger &operator<<(const T &message)
	{
		std::lock_guard<std::mutex> lock(mutex_);

		std::time_t now = std::time(nullptr);
		char buf[20];
		std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S",
			      std::localtime(&now));

		if (log_file.is_open()) {
			log_file << "[" << buf << "] ["
				 << logLevelToString(log_level) << "] "
				 << message << std::endl;
		}

		return *this;
	}

    private:
	Logger()
		: log_level(INFO)
		, log_file()
	{
		std::time_t now = std::time(nullptr);
		char time_buf[20];
		std::strftime(time_buf, sizeof(time_buf), "%Y%m%d_%H%M%S",
			      std::localtime(&now));

		std::string filename =
			"./logs/log_" + std::string(time_buf) + ".log";
		log_file.open(filename, std::ios::out | std::ios::app);
		if (!log_file.is_open()) {
			std::cerr << "Unable to open log file: " << filename
				  << std::endl;
		}
	}

	~Logger()
	{
		if (log_file.is_open()) {
			log_file.close();
		}
	}

	Logger(const Logger &) = delete;
	Logger &operator=(const Logger &) = delete;

	LogLevel log_level;
	std::ofstream log_file;
	std::mutex mutex_;

	std::string logLevelToString(LogLevel level)
	{
		switch (level) {
		case DEBUG:
			return "DEBUG";
		case INFO:
			return "INFO";
		case WARNING:
			return "WARNING";
		case ERROR:
			return "ERROR";
		case FATAL:
			return "FATAL";
		default:
			return "UNKNOWN";
		}
	}
};

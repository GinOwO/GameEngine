#pragma once

#include <string>
#include <json/json.h>
class AWS {
	static bool idle;
	static std::string token;
	static std::string player_id;

    public:
	static bool process_cli(const int32_t argc, const char *argv[]);

	static std::string authenticate_player(const std::string &username,
					       const std::string &password);

	static bool signout();
	static std::string get_player_id();
	static Json::Value read_active(int32_t idle = -1);
	static std::string accept_match(const std::string &opponent_id);
	static Json::Value request_match(const std::string &opponent_id);
	static void reject_match(const std::string &opponent_id);
};
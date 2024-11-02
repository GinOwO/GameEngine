#pragma once

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

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

	static bool request_match(const std::string &requesterId,
				  const std::string &targetId);

	using server = websocketpp::server<websocketpp::config::asio>;
	static void on_message(server *s, websocketpp::connection_hdl hdl,
			       server::message_ptr msg);

	static bool signout();
	static bool toggle_idle();
	static std::string get_player_id();
	static Json::Value read_active(int32_t idle = -1);
};
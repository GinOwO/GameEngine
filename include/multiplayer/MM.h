#pragma once

#include <json/json.h>

class MatchMaking {
	MatchMaking() = default;
	~MatchMaking();

    private:
	bool match_running = false;
	Json::Value player_list;

	bool send_challenge(const std::string &player_id);
	void get_opponents();
	void match_making();
	void end_match();
	void sync();

    public:
	MatchMaking(const MatchMaking &) = delete;
	MatchMaking &operator=(const MatchMaking &) = delete;

	static MatchMaking &get_instance();

	int32_t init(int argc, char const *argv[]);
};
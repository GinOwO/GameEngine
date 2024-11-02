#pragma once

#include <map>
#include <string>
#include <cstdint>

class MatchMaking {
	MatchMaking() = default;

    private:
	bool match_running = false;

	bool send_challenge(const std::string &player_id);
	std::map<std::string, std::string> get_opponents();
	void end_match();
	void sync();

    public:
	MatchMaking(const MatchMaking &) = delete;
	MatchMaking &operator=(const MatchMaking &) = delete;

	static MatchMaking &get_instance();

	int32_t init(int argc, char const *argv[]);
	void match_making();
};
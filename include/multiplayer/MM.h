#pragma once

#include <misc/SafeQueue.h>

#include <map>
#include <string>
#include <cstdint>
#include <thread>

class MatchMaking {
	MatchMaking() = default;

    private:
	std::string connect_url;
	std::string player_name;
	std::string challenged_by;
	std::thread *player_thread = nullptr;
	std::atomic<bool> match_running = false;
	int32_t match_outcome = 0;
	int32_t sock = -1;

	std::map<std::string, std::string> get_opponents();
	void sync_player_queue();
	void
	sync_enemy_queue(SafeQueue<std::pair<int32_t, float> > *enemy_queue);

    public:
	~MatchMaking();
	MatchMaking(const MatchMaking &) = delete;
	MatchMaking &operator=(const MatchMaking &) = delete;

	static MatchMaking &get_instance();

	int32_t init(int argc, char const *argv[]);
	std::string match_making();
};
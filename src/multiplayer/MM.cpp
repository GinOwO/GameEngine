#include <multiplayer/MM.h>

#include <core/SharedGlobals.h>

#include <misc/SafeQueue.h>

#include <multiplayer/AWS.h>
#include <json/json.h>

#include <thread>

MatchMaking::~MatchMaking()
{
	AWS::signout();
}

MatchMaking &MatchMaking::get_instance()
{
	static MatchMaking mm;
	return mm;
}

int32_t MatchMaking::init(int argc, char const *argv[])
{
	if (!AWS::process_cli(argc, argv)) {
		AWS::signout();
		return -1;
	}
	return 0;
}

void MatchMaking::sync()
{
	static SharedGlobals &globals = SharedGlobals::get_instance();
	SafeQueue<std::pair<int32_t, float> > *player_queue = nullptr;
	SafeQueue<std::pair<int32_t, float> > *enemy_queue = nullptr;
	while (!player_queue || !enemy_queue) {
		player_queue =
			static_cast<SafeQueue<std::pair<int32_t, float> > *>(
				globals.player_moves);
		enemy_queue =
			static_cast<SafeQueue<std::pair<int32_t, float> > *>(
				globals.enemy_moves);
	}

	while (match_running) {
		if (player_queue->size()) {
			// Send player queue to other player over sockets
		}
		// Get and store incoming other player moves
	}
}

void MatchMaking::get_opponents()
{
}

void MatchMaking::match_making()
{
}
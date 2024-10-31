#include <multiplayer/MM.h>

#include <json/json.h>

Json::Value MatchMaking::player_list = Json::Value();

int32_t MatchMaking::init()
{
	return 1;
}
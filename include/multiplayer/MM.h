#pragma once

#include <multiplayer/AWS.h>

#include <json/json.h>

class MatchMaking {
	static Json::Value player_list;

    public:
	static int32_t init();
};
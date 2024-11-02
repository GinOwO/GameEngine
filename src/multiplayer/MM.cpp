#include <multiplayer/MM.h>

#include <core/SharedGlobals.h>

#include <misc/SafeQueue.h>

#include <multiplayer/AWS.h>
#include <json/json.h>
#include <ncurses.h>

#include <cstdint>
#include <iostream>

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

std::map<std::string, std::string> MatchMaking::get_opponents()
{
	std::map<std::string, std::string> player_name_id;
	Json::Value opponents = AWS::read_active(1);
	for (std::string &key : opponents.getMemberNames()) {
		player_name_id[opponents[key]["PlayerID"]["S"].asString()] =
			opponents[key]["Nickname"]["S"].asString();
	}
	return player_name_id;
}

void display_menu(int highlight, std::vector<std::string> opponents)
{
	clear();
	static const char header[] = "Idle Online Players";
	mvprintw(0, 2, header);
	for (size_t i = 0; i < opponents.size(); i++) {
		if (i == highlight) {
			attron(A_REVERSE);
			mvprintw(i + 1, 2, opponents[i].c_str());
			attroff(A_REVERSE);
		} else {
			mvprintw(i + 1, 2, opponents[i].c_str());
		}
	}
	refresh();
}

void MatchMaking::match_making()
{
	static const std::string &player_id = AWS::get_player_id();
	std::vector<std::string> opponents_menu{ "REFRESH" };

	for (auto &[id, name] : get_opponents()) {
		if (id != player_id)
			opponents_menu.push_back(name);
	}

	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);

	int32_t highlight = 0;
	int32_t choice = 0;
	int32_t opp = -1;

	while (choice >= 0) {
		display_menu(highlight, opponents_menu);

		int32_t input = getch();
		switch (input) {
		case KEY_UP:
			highlight = (highlight == 0) ?
					    opponents_menu.size() - 1 :
					    highlight - 1;
			break;
		case KEY_DOWN:
			highlight = (highlight == opponents_menu.size() - 1) ?
					    0 :
					    highlight + 1;
			break;
		case 10:
			choice = highlight;
			if (choice == 0) {
				opponents_menu = { "REFRESH" };
				for (auto &[id, name] : get_opponents()) {
					if (id != player_id)
						opponents_menu.push_back(name);
				}
			} else {
				opp = choice;
				choice = -1;
				break;
			}
		default:
			break;
		}
	}
	nocbreak();
	echo();
	endwin();
	std::cout << opp << "\r\n";
}
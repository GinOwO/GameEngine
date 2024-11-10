#include <multiplayer/MM.h>
#ifdef MULTIPLAYER
#include <core/SharedGlobals.h>

#include <misc/SafeQueue.h>
#include <misc/Log.h>

#include <multiplayer/AWS.h>
#include <json/json.h>
#include <ncurses.h>

#include <cmath>
#include <cstdint>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <random>
#include <iomanip>
#include <sstream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <exception>

constexpr int32_t INSTR_BUFFER_SIZE = 129;

MatchMaking &MatchMaking::get_instance()
{
	static MatchMaking mm;
	return mm;
}

MatchMaking::~MatchMaking()
{
	match_running = false;
	if (player_thread != nullptr && player_thread->joinable()) {
		player_thread->join();
	}
	delete player_thread;
}

int32_t MatchMaking::init(int argc, char const *argv[])
{
	if (!AWS::process_cli(argc, argv)) {
		AWS::signout();
		return -1;
	}
	return 0;
}

void MatchMaking::sync_player_queue()
{
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
		perror("Socket creation failed");
		return;
	}

	int opt = 1;
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	sockaddr_in addr{};
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("0.0.0.0");
	std::random_device rd;
	std::uniform_int_distribution<int> port_dist(8000, 8099);
	addr.sin_port = htons(port_dist(rd));

	if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("Bind failed");
		close(sock);
		error = true;
		return;
	}

	sockaddr_in server_addr{};
	server_addr.sin_family = AF_INET;
	inet_pton(
		AF_INET,
		this->connect_url.substr(0, this->connect_url.find(':')).c_str(),
		&server_addr.sin_addr);

	server_addr.sin_port = htons(
		atoi(this->connect_url.substr(this->connect_url.find(':') + 1)
			     .c_str()));

	if (connect(sock, (struct sockaddr *)&server_addr,
		    sizeof(server_addr)) < 0) {
		perror("Connection failed");
		close(sock);
		error = true;
		Logger::get_instance() << this->connect_url;
		return;
	}

	if (send(sock, AWS::get_player_id().c_str(),
		 AWS::get_player_id().size(), 0) < 0) {
		perror("Handshaking failed");
		close(sock);
		error = true;
		return;
	}
	char buffer[2048];
	int n = recv(sock, buffer, 2048, 0);
	if (n < 0) {
		perror("Handshaking failed");
		close(sock);
		error = true;
		return;
	}
	handshaked = true;

	static SharedGlobals &globals = SharedGlobals::get_instance();
	SafeQueue<std::pair<int32_t, std::vector<float> > > *player_queue =
		nullptr;
	SafeQueue<std::pair<int32_t, std::vector<float> > > *enemy_queue =
		nullptr;

	while (!player_queue || !enemy_queue) {
		player_queue = static_cast<
			SafeQueue<std::pair<int32_t, std::vector<float> > > *>(
			globals.player_moves);
		enemy_queue = static_cast<
			SafeQueue<std::pair<int32_t, std::vector<float> > > *>(
			globals.enemy_moves);

		if (!player_queue || !enemy_queue) {
			std::this_thread::sleep_for(
				std::chrono::milliseconds(10));
		}
	}

	std::thread enemy_thread(&MatchMaking::sync_enemy_queue, this,
				 enemy_queue);

	while (match_running) {
		if (!player_queue->size())
			continue;

		auto [x, y] = player_queue->pop();
		if (x == -1)
			continue;
		std::ostringstream oss;
		oss << x << std::fixed << std::setprecision(6);
		for (auto &c : y)
			oss << ',' << c;

		std::string message = oss.str();
		if (message.size() < INSTR_BUFFER_SIZE) {
			message.append(INSTR_BUFFER_SIZE - message.size(),
				       '\0');
		} else if (message.size() > INSTR_BUFFER_SIZE) {
			message = message.substr(0, 128) + "\0";
		}

		if (send(sock, message.c_str(), message.size(), 0) < 0) {
			perror("Send failed");
			break;
		}
	}

	if (enemy_thread.joinable()) {
		enemy_thread.join();
	}

	close(sock);
	sock = -1;
}

void MatchMaking::sync_enemy_queue(
	SafeQueue<std::pair<int32_t, std::vector<float> > > *enemy_queue)
{
	static char buffer[INSTR_BUFFER_SIZE];
	while (match_running) {
		struct timeval timeout = { 60, 0 };
		setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO,
			   (const char *)&timeout, sizeof timeout);

		int recv_size = recv(sock, buffer, sizeof(buffer) - 1, 0);
		if (recv_size <= 0) {
			if (recv_size == 0 || errno == EWOULDBLOCK ||
			    errno == EAGAIN) {
#ifdef AWS_DEBUG
				std::cout
					<< "(AWS) No data received in 60 seconds. Ending match.\n";
#endif
				this->match_outcome = -1;
				this->match_running = false;
			}
			break;
		}

		buffer[recv_size] = '\0';
		std::string received_data(buffer);

		if (recv_size < 1)
			continue;
		size_t comma_pos = received_data.find(',');
		if (comma_pos != std::string::npos) {
			try {
				int32_t x = std::stoi(
					received_data.substr(0, comma_pos));

				std::vector<float> y;
				std::string floats_part =
					received_data.substr(comma_pos + 1);
				std::istringstream ss(floats_part);
				std::string token;
				while (std::getline(ss, token, ',')) {
					y.push_back(std::stof(token));
				}
				enemy_queue->push({ x, y });
			} catch (const std::invalid_argument &e) {
				// std::cerr << "MM:\t\tMalformed state received: "
				// 	  << received_data << '\n';
			}
		}
	}
}

void display_menu(int highlight, std::vector<std::string> &opponents)
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

std::map<std::string, std::string> MatchMaking::get_opponents()
{
	challenged_by = "";
	std::map<std::string, std::string> player_name_id;
	Json::Value opponents = AWS::read_active();
	for (std::string &key : opponents.getMemberNames()) {
		if (opponents[key]["PlayerID"]["S"].asString() ==
		    AWS::get_player_id()) {
			challenged_by =
				opponents[key]["ChallengedBy"]["S"].asString();
			player_name =
				opponents[key]["Nickname"]["S"].asString();
		} else if (opponents[key]["Idle"]["BOOL"].asBool()) {
			player_name_id[opponents[key]["Nickname"]["S"]
					       .asString()] =
				opponents[key]["PlayerID"]["S"].asString();
		}
	}
	return player_name_id;
}

std::string MatchMaking::match_making()
{
	static const std::string &player_id = AWS::get_player_id();
	std::map<std::string, std::string> opponents = get_opponents(),
					   rev_opponents;
	std::vector<std::string> opponents_menu{ player_name + " (You)" };
	for (const auto &[name, id] : opponents) {
		opponents_menu.push_back(name);
		rev_opponents[id] = name;
	}
	Json::Value response;
	int32_t opp;
	int32_t highlight = 0;
	int32_t choice = -1;
	bool quit = false;

	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);

	auto update = [&] {
		static auto last_refresh_time =
			std::chrono::steady_clock::now();
		if (std::chrono::steady_clock::now() - last_refresh_time >=
		    std::chrono::seconds(3)) {
			last_refresh_time = std::chrono::steady_clock::now();
			opponents_menu.clear();
			rev_opponents.clear();
			opponents_menu.push_back(player_name + " (You)");
			opponents = get_opponents();
			for (const auto &[name, id] : opponents) {
				opponents_menu.push_back(name);
				rev_opponents[id] = name;
			}

			if (!this->challenged_by.empty()) {
				int response = -1;
				WINDOW *popup = newwin(5, 40, 15, 15);
				box(popup, 0, 0);
				mvwprintw(popup, 1, 1,
					  "You have a match request from %s.",
					  rev_opponents[challenged_by].c_str());
				mvwprintw(popup, 2, 1, "Accept? (y/n)");
				wrefresh(popup);

				while (response == -1) {
					int ch = wgetch(popup);
					if (ch == 'y' || ch == 'Y') {
						response = 0;
					} else if (ch == 'n' || ch == 'N') {
						response = 1;
					}
				}

				delwin(popup);

				if (response == 0) {
					connect_url = AWS::accept_match(
						challenged_by);
					quit = true;
					player_number = 2;
				} else {
					AWS::reject_match(challenged_by);
				}
			}
		}
	};

	auto input = [&] {
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
			if (highlight <= 0 ||
			    highlight >= opponents_menu.size()) {
				highlight = 0;
			} else {
				opp = highlight;
				choice = -1;
			}
			break;
		default:
			break;
		}

		refresh();
	};

	while (!quit) {
		opp = -1;
		while (!quit && opp == -1) {
			update();
			if (!quit) {
				display_menu(highlight, opponents_menu);
				input();
			}
		}
		if (choice != -1 || quit)
			continue;
		static const char match_req[] =
			"Requesting Match, please wait...";
		mvprintw(0, 2, match_req);
		refresh();
		response = AWS::request_match(opponents[opponents_menu[opp]]);
		if (response.size() &&
		    response["message"].asString() == "Challenge accepted") {
			connect_url = response["connect_url"].asString();
			quit = true;
			player_number = 1;
		}
		refresh();
	}

	endwin();
	match_running = true;
	player_thread = new std::thread(&MatchMaking::sync_player_queue, this);
#ifdef AWS_DEBUG
	Logger::get_instance()
		<< "(MM):\t\t Connect URL: " << connect_url << '\n';
#endif
	return connect_url;
}

bool MatchMaking::is_success()
{
	return !error;
}

bool MatchMaking::is_handshaking()
{
	return !handshaked;
}

bool MatchMaking::is_match_running()
{
	return match_running;
}

void MatchMaking::set_match_running(bool state)
{
	match_running = state;
}

int32_t MatchMaking::get_match_outcome()
{
	return match_outcome;
}

int32_t MatchMaking::get_player_number()
{
	return player_number;
}

#endif
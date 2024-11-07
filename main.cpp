#include <misc/glad.h>
#include <GLFW/glfw3.h>

#include <core/Engine.h>
#include <graphics/Shader.h>

#include <csignal>
#include <cstdlib>
#include <iostream>

#ifdef MULTIPLAYER

#include <core/SharedGlobals.h>

#include <multiplayer/AWS.h>
#include <multiplayer/MM.h>

#endif

void signal_handler(int signal)
{
	std::cerr << "Caught signal " << signal << ", executing cleanup.\n";
#ifdef MULTIPLAYER
	AWS::signout();
#endif
	std::exit(EXIT_FAILURE);
}

void setup_signal_handlers()
{
	const int signals[] = { SIGINT,	 SIGTERM, SIGILL,
				SIGABRT, SIGFPE,  SIGPIPE };

	for (int sig : signals) {
		std::signal(sig, signal_handler);
	}
}

int main(int argc, char const *argv[])
{
	setup_signal_handlers();
#ifdef MULTIPLAYER
	MatchMaking &MM = MatchMaking::get_instance();
	if (MM.init(argc, argv)) {
		return EXIT_FAILURE;
	}
	MM.match_making();
	while (MM.is_handshaking() && MM.is_success())
		std::this_thread::sleep_for(std::chrono::milliseconds(5));

	if (MM.is_success()) {
#endif
		glfwInit();
		Engine engine;
		engine.start();
		glfwTerminate();

#ifdef MULTIPLAYER
	}
	switch (MM.get_match_outcome()) {
	case -1:
		std::cout << "Match cancelled\n";
		break;
	case 1:
		std::cout << "Player 1 won\n";
		break;
	case 2:
		std::cout << "Player 2 won\n";
		break;
	default:
		break;
	}
	AWS::signout();
#endif
	return EXIT_SUCCESS;
}
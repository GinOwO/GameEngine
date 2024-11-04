#include <misc/glad.h>
#include <GLFW/glfw3.h>

#include <core/Engine.h>
#include <graphics/Shader.h>

#ifdef MULTIPLAYER

#include <core/SharedGlobals.h>

#include <multiplayer/AWS.h>
#include <multiplayer/MM.h>

#endif

int main(int argc, char const *argv[])
{
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
	}
#endif

	return EXIT_SUCCESS;
}
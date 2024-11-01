#include <misc/glad.h>
#include <GLFW/glfw3.h>

#include <core/Engine.h>
#include <graphics/Shader.h>

#ifdef MULTIPLAYER

#include <core/SharedGlobals.h>
#include <multiplayer/MM.h>

#endif

int main(int argc, char const *argv[])
{
#ifdef MULTIPLAYER
	MatchMaking &MM = MatchMaking::get_instance();
	if (MM.init(argc, argv)) {
		return EXIT_FAILURE;
	}

#endif
	glfwInit();
	// Engine engine;
	// engine.start();
	glfwTerminate();

	return EXIT_SUCCESS;
}
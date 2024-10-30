#include <misc/glad.h>
#include <GLFW/glfw3.h>

#include <core/Engine.h>
#include <graphics/Shader.h>

#ifdef MULTIPLAYER

#include <multiplayer/AWS.h>

#endif

int main(int argc, char const *argv[])
{
#ifdef MULTIPLAYER
	if (!AWS::process_cli(argc, argv)) {
		AWS::signout();
		return EXIT_FAILURE;
	}
#endif
	glfwInit();
	// Engine engine;
	// engine.start();
	glfwTerminate();

#ifdef MULTIPLAYER
	if (!AWS::signout()) {
		return EXIT_FAILURE;
	}
#endif
	return EXIT_SUCCESS;
}
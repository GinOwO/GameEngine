#include <misc/glad.h>
#include <GLFW/glfw3.h>

#include <core/Engine.h>
#include <graphics/Shader.h>

int main(int argc, char const *argv[])
{
	glfwInit();

	Engine engine;
	engine.start();

	glfwTerminate();

	return EXIT_SUCCESS;
}
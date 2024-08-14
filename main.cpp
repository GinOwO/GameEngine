#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <core/Engine.h>
#include <graphics/ShaderIO.h>

#include <cstdlib>

int main(int argc, char const *argv[])
{
	glfwInit();
	Engine engine = Engine();
	engine.start();

	glfwTerminate();

	return EXIT_SUCCESS;
}
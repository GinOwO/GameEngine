#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Engine.h>
#include <shaderIO.h>

#include <cstdlib>

int main(int argc, char const *argv[])
{
	glfwInit();
	Engine engine = Engine();
	engine.start();

	glfwTerminate();

	return EXIT_SUCCESS;
}
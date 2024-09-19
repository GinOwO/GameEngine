#include <misc/glad.h>
#include <GLFW/glfw3.h>

#include <core/Engine.h>
#include <graphics/Shader.h>

#include <PxPhysics.h>
#include <PxPhysicsAPI.h>

#include <cstdlib>

int main(int argc, char const *argv[])
{
	glfwInit();
	Engine engine;
	engine.start();

	glfwTerminate();

	return EXIT_SUCCESS;
}
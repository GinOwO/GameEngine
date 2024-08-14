#include <game/Game.h>

#include <Mesh.h>
#include <Vertex.h>
#include <Input.h>
#include <Window.h>
#include <RenderUtil.h>
#include <shaderIO.h>

Game::Game(Input &input_, Window &window)
	: input_handler(input_)
	, window(window)
{
	vertices = {
		Vertex(Vector3f(0.0f, 0.5f, 0.0f)), // Top vertex
		Vertex(Vector3f(0.5f, -0.5f, 0.0f)), // Bottom right vertex
		Vertex(Vector3f(-0.5f, -0.5f, -1.0f)), // Bottom left vertex
	};
	meshes.push_back({ vertices, create_shader_program(
					     "./shaders/vertShader.vert",
					     "./shaders/fragShader.frag") });

	vertices = {
		Vertex(Vector3f(0.0f, 0.5f, 0.0f)), // Top vertex
		Vertex(Vector3f(0.5f, -0.5f, 0.0f)), // Bottom right vertex
		Vertex(Vector3f(-1.0f, -0.5f, 0.0f)), // Bottom left vertex
	};
	meshes.push_back({ vertices, create_shader_program(
					     "./shaders/vertShader.vert",
					     "./shaders/fragShader1.frag") });

	render_order = { 0, 1 };
}

void Game::input()
{
	glfwPollEvents();
}

void Game::update()
{
}

void Game::render()
{
	RenderUtil::clear_screen();
	for (int &index : render_order) {
		meshes[index].draw();
	}
	window.swap_buffers();
}
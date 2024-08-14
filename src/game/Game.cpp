#include <game/Game.h>

#include <graphics/ShaderIO.h>

#include <graphics/Mesh.h>
#include <graphics/Vertex.h>

#include <core/Input.h>
#include <core/Window.h>
#include <core/RenderUtil.h>

#include <iostream>

Game::Game(Input &input_, Window &window)
	: input_handler(input_)
	, window(window)
{
	vertices = {
		Vertex(Vector3f(0.0f, 0.5f, 0.0f)), // Top vertex
		Vertex(Vector3f(0.5f, -0.5f, 0.0f)), // Bottom right vertex
		Vertex(Vector3f(-0.5f, -0.5f, 0.0f)), // Bottom left vertex
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

	vertices = {
		Vertex(Vector3f(0.0f, 0.5f, 0.0f)), // Top vertex
		Vertex(Vector3f(0.5f, -1.0f, 0.0f)), // Bottom right vertex
		Vertex(Vector3f(-0.0f, -0.5f, 0.0f)), // Bottom left vertex
	};
	meshes.push_back({ vertices, create_shader_program(
					     "./shaders/vertShader.vert",
					     "./shaders/fragShader2.frag") });
	render_order = { 1, 0, 2 };
}

void Game::input()
{
	if (input_handler.is_key_pressed(GLFW_KEY_F)) {
		std::cout << "F is pressed owob\n";
	}

	if (input_handler.is_mouse_down(GLFW_MOUSE_BUTTON_1)) {
		std::cout << "Mouse 1 is pressed owob\n";
	}
}

void Game::update()
{
}

void Game::render()
{
	RenderUtil::clear_screen();
	for (int i = meshes.size() - 1; i >= 0; i--) {
		meshes[render_order[i]].draw();
	}
	window.swap_buffers();
}
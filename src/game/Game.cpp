#include <game/Game.h>

#include <graphics/Shader.h>

#include <graphics/Mesh.h>
#include <graphics/Vertex.h>

#include <core/Input.h>
#include <core/Window.h>
#include <core/Timer.h>
#include <core/RenderUtil.h>

#include <iostream>
#include <cmath>

Game::Game(Input &input_handler, Window &window, Timer &timer)
	: input_handler(input_handler)
	, window(window)
	, timer(timer)
{
	vertices = {
		Vertex(Vector3f(0.0f, 0.5f, 0.0f)), // Top vertex
		Vertex(Vector3f(0.5f, -0.5f, 0.0f)), // Bottom right vertex
		Vertex(Vector3f(-0.5f, -0.5f, 0.0f)), // Bottom left vertex
	};
	Shader sh("./shaders/vertShader.vert", "./shaders/fragShader.frag");
	sh.add_uniform("uniformTimerDelta");
	meshes.push_back({ vertices, sh });

	// vertices = {
	// 	Vertex(Vector3f(0.0f, 0.5f, 0.0f)), // Top vertex
	// 	Vertex(Vector3f(0.5f, -0.5f, 0.0f)), // Bottom right vertex
	// 	Vertex(Vector3f(-1.0f, -0.5f, 0.0f)), // Bottom left vertex
	// };
	// meshes.push_back({ vertices, Shader("./shaders/vertShader.vert",
	// 				    "./shaders/fragShader1.frag") });

	// vertices = {
	// 	Vertex(Vector3f(0.0f, 0.5f, 0.0f)), // Top vertex
	// 	Vertex(Vector3f(0.5f, -1.0f, 0.0f)), // Bottom right vertex
	// 	Vertex(Vector3f(-0.0f, -0.5f, 0.0f)), // Bottom left vertex
	// };
	// meshes.push_back({ vertices, Shader("./shaders/vertShader.vert",
	// 				    "./shaders/fragShader2.frag") });
	render_order = { 0 };
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

float temp = 0.0f;

void Game::update()
{
	temp += timer.get_delta_time();
	meshes[0].get_shader_program().set_uniform("uniformTimerDelta",
						   std::sin(temp));
	if (temp > 3.14f)
		temp = -3.14;
}

void Game::render()
{
	RenderUtil::clear_screen();
	for (int i = meshes.size() - 1; i >= 0; i--) {
		meshes[render_order[i]].draw();
	}
	window.swap_buffers();
}
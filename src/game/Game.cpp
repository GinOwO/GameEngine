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
	Mesh mesh = Mesh::load_mesh("./assets/objects/vergil_chair.obj");
	Shader sh("./shaders/vertShader.vert", "./shaders/fragShader.frag");
	sh.add_uniform("transform");
	mesh.set_shader_program(sh);

	meshes.push_back(mesh);
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
	transform.set_projection(70.0f, window.get_window_width(),
				 window.get_window_height(), .1f, 1000.0f);

	temp += timer.get_delta_time();

	float sint = std::sinf(temp);

	transform.set_translation({ 0, 0, 10 });
	transform.set_rotation({ 0, 270, -35 });
	// transform.set_scale({ .5, .5, .5 });

	Matrix4f transformation =
		Matrix4f::flip_matrix(transform.get_projected_transformation());

	meshes[0].get_shader_program().set_uniform("transform", transformation);
}

void Game::render()
{
	RenderUtil::clear_screen();
	for (int i = meshes.size() - 1; i >= 0; i--) {
		meshes[render_order[i]].draw();
	}
	window.swap_buffers();
}
#include <game/Game.h>

#include <misc/glad.h>
#include <GLFW/glfw3.h>

#include <graphics/Mesh.h>
#include <graphics/Vertex.h>
#include <graphics/Material.h>
#include <graphics/Textures.h>

#include <graphics/BasicShader.h>
#include <graphics/PhongShader.h>

#include <core/Input.h>
#include <core/Window.h>
#include <core/Timer.h>
#include <core/Camera.h>
#include <core/RenderUtil.h>

#include <iostream>
#include <cmath>

// #define _DEBUG_CAMERA_ON

Material material;
PhongShader sh;

Game::Game(Input &input_handler, Window &window, Timer &timer, Camera &camera)
	: input_handler(input_handler)
	, window(window)
	, timer(timer)
	, camera(camera)
{
	// Mesh mesh = Mesh::load_mesh("./assets/objects/cube.obj");
	//     "./assets/objects/cube_texture.png");
	Mesh mesh;
	std::vector<Vertex> vertices{
		{ { -1, -1, 0 }, { 0.0, 0.0 } },
		{ { 0, 1, 0 }, { 0.5, 0.0 } },
		{ { 1, -1, 0 }, { 1.0, 0.0 } },
		{ { 0, -1, 1 }, { 0.0, 0.5 } },
	};
	std::vector<int> indices{ 0, 1, 3, 3, 1, 2, 2, 1, 0, 0, 2, 3 };

	material = Material(
		Texture::load_texture("./assets/objects/test_texture.png"),
		{ 1, 1, 1 });

	sh = PhongShader("./shaders/phongVertShader.vert",
			 "./shaders/phongFragShader.frag");

	mesh.add_vertices(vertices, indices);

	mesh.set_material(material);

	meshes.push_back(mesh);
	render_order = { 0 };

	camera.set_position({ 0, 0, -15 });
}

void Game::input()
{
#ifndef _CAMERA_DISABLED
	float move_multiplier = 10.0f * timer.get_delta_time();
	float rotate_sensitivity = 40.0f * timer.get_delta_time();

	if (input_handler.is_key_pressed(GLFW_KEY_W)) {
		camera.move_camera(camera.get_forward(), move_multiplier);
	}
	if (input_handler.is_key_pressed(GLFW_KEY_S)) {
		camera.move_camera(camera.get_forward(), -move_multiplier);
	}
	if (input_handler.is_key_pressed(GLFW_KEY_A)) {
		camera.move_camera(camera.get_left(), move_multiplier);
	}
	if (input_handler.is_key_pressed(GLFW_KEY_D)) {
		camera.move_camera(camera.get_right(), move_multiplier);
	}

	if (input_handler.is_mouse_down(GLFW_MOUSE_BUTTON_2)) {
		const double *delta = input_handler.get_mouse_pos_delta();
		float dx = delta[0], dy = delta[1];

		if (dx != 0) {
			camera.rotate_x(dx * rotate_sensitivity);
		}
		if (dy != 0) {
			camera.rotate_y(dy * rotate_sensitivity);
		}
	}
#endif
}

float temp = 0.0f;

void Game::update()
{
	transform.set_projection(70.0f, window.get_window_width(),
				 window.get_window_height(), .1f, 1000.0f);

	temp += timer.get_delta_time();

	float sint = std::sin(temp);

	// transform.set_translation({ 0, 0, 0 });
	transform.set_rotation({ 0, sint * 180, 0 });
	// transform.set_scale({ .5, .5, .5 });

	Matrix4f projection_matrix =
		Matrix4f::flip_matrix(transform.get_projected_camera(camera));

	Matrix4f transformation_matrix =
		Matrix4f::flip_matrix(transform.get_transformation());

#ifdef _DEBUG_CAMERA_ON
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			std::cout << transformation.get(i, j) << ' ';
		}
		std::cout << '\n';
	}
	std::cout << "-----------------------------------\n";
#endif
	sh.get_directional_light().base_light.intensity = 1.0;
	sh.update_uniforms(transformation_matrix, projection_matrix,
			   meshes[0].get_material());
}

void Game::render()
{
	RenderUtil::clear_screen();
	for (int i = meshes.size() - 1; i >= 0; i--) {
		sh.use_program();
		meshes[render_order[i]].draw();
	}
	window.swap_buffers();
}
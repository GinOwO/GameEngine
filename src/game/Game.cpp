#include <game/Game.h>

#include <misc/glad.h>
#include <GLFW/glfw3.h>

#include <graphics/Mesh.h>
#include <graphics/Vertex.h>
#include <graphics/Material.h>
#include <graphics/Texture.h>

#include <graphics/BasicShader.h>
#include <graphics/PhongShader.h>
#include <graphics/DirectionalLight.h>
#include <graphics/PointLight.h>
#include <graphics/SpotLight.h>

#include <core/Input.h>
#include <core/Window.h>
#include <core/Timer.h>
#include <core/Camera.h>
#include <core/RenderUtil.h>

#include <iostream>
#include <cmath>

// #define _DEBUG_CAMERA_ON

Game::Game(Input &input_handler, Window &window, Timer &timer, Camera &camera)
	: input_handler(input_handler)
	, window(window)
	, timer(timer)
	, camera(camera)
{
	// Mesh mesh = Mesh::load_mesh("./assets/objects/cube.obj");
	//     "./assets/objects/cube_texture.png");
	Mesh mesh;
	// std::vector<Vertex> vertices{
	// 	{ { -1.0f, -1.0f, 0.5773f }, { 0.0f, 0.0f } },
	// 	{ { 0.0f, -1.0f, -1.15475f }, { 0.5f, 0.0f } },
	// 	{ { 1.0f, -1.0f, 0.5773f }, { 0.5f, 0.0f } },
	// 	{ { 0.0f, 1.0f, 0.0f }, { 0.5f, 1.0f } },
	// };
	// std::vector<int> indices{ 0, 3, 1, 1, 3, 2, 2, 3, 0, 1, 2, 0 };

	float field_width = 10.0f, field_depth = 10.0f;
	std::vector<Vertex> vertices{
		{ { -field_width, 0.0f, -field_depth }, { 0.0f, 0.0f } },
		{ { -field_width, 0.0f, field_depth * 3 }, { 0.0f, 1.0f } },
		{ { field_width * 3, 0.0f, -field_depth }, { 1.0f, 0.0f } },
		{ { field_width * 3, 0.0f, field_depth * 3 }, { 1.0f, 1.0f } }
	};

	std::vector<int> indices{ 0, 1, 2, 2, 1, 3 };

	phong_shader.load_shaders("./shaders/phongVertShader.vert",
				  "./shaders/phongFragShader.frag");

	mesh.add_vertices(vertices, indices, true);

	mesh.set_material(Material(
		Texture::load_texture("./assets/objects/test_texture.png"),
		{ 1, 1, 1 }, { 1, 8 }));

	meshes.push_back(mesh);
	render_order = { 0 };

	camera.set_position({ 0, 0, -10 });

	phong_shader.set_ambient_light({ 0.1 });
	// phong_shader.set_directional_light({ { 1.0f, 0.8f }, 1 });

	PointLight point_light1{
		{ "#EEDD82", 0.7f }, { 0, 0, 0.05 }, { -2, 0, 1 }, 40
	};

	PointLight point_light2{
		{ "#0088FF", 1.0f }, { 0, 0, 1 }, { 2, 0, 1 }, 10
	};

	SpotLight spot_light1{ point_light1, { 1, 1, 1 }, 0.7f };

	// phong_shader.set_point_lights({ point_light1, point_light2 });
	phong_shader.set_spot_lights({ spot_light1 });
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
	if (input_handler.is_key_pressed(GLFW_KEY_Q)) {
		camera.move_camera(camera.get_up(), move_multiplier);
	}
	if (input_handler.is_key_pressed(GLFW_KEY_E)) {
		camera.move_camera(camera.get_up(), -move_multiplier);
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

	float sint = ((2 * std::sin(temp) + 1.0f / 2.0f) + 10);
	float cost = ((2 * std::cos(temp) + 1.0f / 2.0f) + 10);

	transform.set_translation({ 0, -1, 5 });

	// transform.set_rotation({ 0, sint * 180, 0 });
	// transform.set_scale({ .5, .5, .5 });

	// phong_shader.point_lights[0].position =
	// 	Vector3f{ 15.0f - sint, 0, cost };
	// phong_shader.point_lights[1].position =
	// 	Vector3f{ 15.0f - cost, 0, sint };

	Vector3f camera_pos = camera.get_position();
	phong_shader.spot_lights[0].set_direction(camera.get_forward());
	phong_shader.spot_lights[0].point_light.position = {
		camera_pos.getX(), camera_pos.getY(), camera_pos.getZ() + 0.5f
	};

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
	phong_shader.update_uniforms(transformation_matrix, projection_matrix,
				     meshes[0].get_material(),
				     camera.get_position());
}

void Game::render()
{
	RenderUtil::clear_screen();
	for (int i = meshes.size() - 1; i >= 0; i--) {
		phong_shader.use_program();
		meshes[render_order[i]].draw();
	}
	window.swap_buffers();
}
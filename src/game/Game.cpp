#include <game/Game.h>

#include <misc/glad.h>
#include <GLFW/glfw3.h>

#include <graphics/Mesh.h>
#include <graphics/Vertex.h>
#include <graphics/Material.h>
#include <graphics/Texture.h>

#include <game/MeshRenderer.h>

#include <iostream>
#include <cmath>

Game::Game()
	: root(new GameObject(this->transform))
{
	float field_width = 10.0f, field_depth = 10.0f;
	std::vector<Vertex> vertices{
		{ { -field_width, 0.0f, -field_depth }, { 0.0f, 0.0f } },
		{ { -field_width, 0.0f, field_depth * 3 }, { 0.0f, 1.0f } },
		{ { field_width * 3, 0.0f, -field_depth }, { 1.0f, 0.0f } },
		{ { field_width * 3, 0.0f, field_depth * 3 }, { 1.0f, 1.0f } }
	};

	std::vector<int> indices{ 0, 1, 2, 2, 1, 3 };

	Mesh mesh(vertices, indices, true);
	Material material(
		Texture::load_texture("./assets/objects/test_texture.png"),
		{ 1, 1, 1 }, { 1, 8 });

	root->add_component(new MeshRenderer(mesh, material));

	// camera.set_position({ 0, 0, -10 });

	shader.load_shader("shaders/vertShader.vert",
			   "shaders/fragShader.frag");
}

void Game::input()
{
	camera.input();
	root->input();
}

void Game::update()
{
	transform.set_projection(70.0f, window.get_window_width(),
				 window.get_window_height(), .1f, 1000.0f);
	transform.set_translation(0, -1, 5);
	root->update();
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			std::cout
				<< transform.get_projected_camera(camera).get(i,
									      j)
				<< ' ';
		}
		std::cout << '\n';
	}
	std::cout << "-----------------------------------\n";
}

void Game::render()
{
	root->render();
}
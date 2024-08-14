#pragma once

#include <graphics/Mesh.h>
#include <graphics/Vertex.h>

#include <core/Input.h>
#include <core/Window.h>

#include <vector>

class Game {
    private:
	Input &input_handler;
	Window &window;
	std::vector<Vertex> vertices;
	std::vector<Mesh> meshes;
	std::vector<int> render_order;

    public:
	Game(Input &input_, Window &window);

	void input();
	void update();
	void render();
};
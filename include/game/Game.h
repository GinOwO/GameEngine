#pragma once

#include <Mesh.h>
#include <Vertex.h>
#include <Input.h>
#include <Window.h>

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
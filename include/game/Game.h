#pragma once

#include <Mesh.h>
#include <Vertex.h>
#include <Input.h>

#include <vector>

class Game {
    private:
	Input &input_handler;
	std::vector<Vertex> vertices;
	Mesh mesh;

    public:
	Game(Input &input_);

	void input();
	void update();
	void render();
};
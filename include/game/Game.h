#pragma once

#include <graphics/Mesh.h>
#include <graphics/Vertex.h>

#include <core/Input.h>
#include <core/Window.h>
#include <core/Timer.h>

#include <math/Transform.h>

#include <vector>

class Game {
    private:
	Input &input_handler;
	Window &window;
	Timer &timer;

	std::vector<Mesh> meshes;
	std::vector<int> render_order;

	Transform transform;

    public:
	Game(Input &input_handler, Window &window, Timer &timer);

	void input();
	void update();
	void render();
};
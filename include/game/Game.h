#pragma once

#include <core/Input.h>
#include <core/Window.h>
#include <core/Timer.h>

#include <graphics/Mesh.h>
#include <graphics/Vertex.h>
#include <graphics/PhongShader.h>

#include <math/Transform.h>

#include <vector>

class Game {
    private:
	Input &input_handler;
	Window &window;
	Timer &timer;
	Camera &camera;
	PhongShader &phong_shader = PhongShader::get_instance();

	std::vector<Mesh> meshes;
	std::vector<int> render_order;

	Transform transform;

    public:
	Game(Input &input_handler, Window &window, Timer &timer,
	     Camera &camera);

	void input();
	void update();
	void render();
};
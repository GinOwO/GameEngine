#pragma once

#include <core/Input.h>
#include <core/Window.h>
#include <core/Timer.h>
#include <core/Camera.h>

#include <graphics/Mesh.h>
#include <graphics/Vertex.h>
#include <graphics/BasicShader.h>
#include <graphics/PhongShader.h>

#include <math/Transform.h>

#include <game/GameObject.h>

#include <vector>

class Game {
    private:
	Input &input_handler = Input::get_instance();
	Window &window = Window::get_instance();
	Timer &timer = Timer::get_instance();
	Camera &camera = Camera::get_instance();
	BasicShader &shader = BasicShader::get_instance();
	PhongShader &phong_shader = PhongShader::get_instance();

	GameObject *root;

	Transform transform;

    public:
	Game();

	void input();
	void update();
	void render();
};
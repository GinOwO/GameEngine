#pragma once

#include <core/Input.h>
#include <core/Window.h>
#include <core/Timer.h>
#include <core/Camera.h>

#include <graphics/Mesh.h>
#include <graphics/Vertex.h>
#include <graphics/Shader.h>
#include <graphics/BasicShader.h>
#include <graphics/PhongShader.h>

#include <math/Transform.h>

#include <game/GameObject.h>

#include <vector>

class Game {
    private:
	GameObject *root = nullptr;

    public:
	virtual void init() = 0;

	void input()
	{
		get_root_object()->input();
	};
	void update()
	{
		get_root_object()->update();
	};
	void render(Shader &shader)
	{
		get_root_object()->render(shader);
	};

	GameObject *get_root_object() noexcept
	{
		if (root == nullptr) {
			root = new GameObject();
		}
		return root;
	}
};
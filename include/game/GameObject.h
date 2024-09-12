#pragma once

#include <vector>

#include <math/Transform.h>

#include <graphics/Shader.h>

#include <game/GameComponent.h>

class GameObject {
	std::vector<GameObject *> children;
	std::vector<GameComponent *> components;

    public:
	Transform transform;
	GameObject();

	void input();
	void update();
	void render(Shader &shader);

	void add_child(GameObject *obj);
	void add_component(GameComponent *obj);
};
#pragma once

#include <math/Transform.h>

#include <game/GameComponent.h>

#include <vector>

class GameObject {
	std::vector<GameObject *> children;
	std::vector<GameComponent *> components;

    public:
	Transform &transform;
	GameObject(Transform &transform);

	void input();
	void update();
	void render();

	void add_child(GameObject *obj);
	void add_component(GameComponent *obj);
};
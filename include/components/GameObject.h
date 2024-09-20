#pragma once

#include <math/Transform.h>

#include <graphics/Shader.h>

#include <components/GameComponent.h>

#include <vector>

class GameObject {
    private:
	std::vector<GameObject *> children;

	std::vector<GameComponent *> components;

    public:
	~GameObject();

	Transform transform{};

	GameObject();

	virtual void input(float delta = 0);

	virtual void update(float delta = 0);

	virtual void render(Shader &shader);

	virtual void reset();

	GameObject *add_child(GameObject *obj);

	GameObject *add_component(GameComponent *obj);

	void add_to_rendering_engine();
};

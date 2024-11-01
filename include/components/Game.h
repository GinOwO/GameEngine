#pragma once

#include <graphics/Shader.h>

#include <btBulletDynamicsCommon.h>

#include <core/SharedGlobals.h>
#include <components/GameObject.h>

#include <physics/Collision.h>
class Game {
    private:
	GameObject *root = nullptr;

    public:
	~Game()
	{
		delete root;
	}

	virtual void init() = 0;

	void input(float delta = 0)
	{
		get_root_object()->input(delta);
	};

	void update(float delta = 0)
	{
		SharedGlobals &globals = SharedGlobals::get_instance();
		globals.dynamics_world->stepSimulation(delta);

		get_root_object()->update(delta);
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

#pragma once

#include <components/GameObject.h>
#include <physics/Collision.h>
#include <btBulletDynamicsCommon.h>

class PlayerMovement : public GameComponent {
    private:
	bool on_ground = false;
	btVector3 velocity;
	float gravity = -9.8f;
	float jump_strength = 10.0f;

    public:
	void update(float deltaTime) override
	{
		// Apply gravity if not on the ground
		if (!on_ground) {
			velocity.setY(velocity.getY() + gravity * deltaTime);
		}

		// Move the player
		move_player(deltaTime);
	}

	void jump()
	{
		if (on_ground) {
			velocity.setY(jump_strength);
			on_ground = false;
		}
	}

	void move_player(float deltaTime)
	{
		// Handle player movement input and apply velocity
		// Update player position based on velocity
		btVector3 new_position =
			game_object->get_position() + velocity * deltaTime;
		game_object->set_position(new_position);
	}

	void set_on_ground(bool value)
	{
		on_ground = value;
	}
};

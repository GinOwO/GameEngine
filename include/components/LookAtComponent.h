#pragma once

#include <math/Transform.h>

#include <graphics/Shader.h>

#include <core/SharedGlobals.h>
#include <components/GameComponent.h>

class LookAtComponent : public GameComponent {
	Transform *target;
	double time_delay = 0;
	double current_delay = 0;

    public:
	LookAtComponent(double delay = 0.0f, Transform *target = nullptr)
		: target(target)
		, time_delay(delay) {};

	void update(float delta) override
	{
		current_delay += delta;
		if (current_delay >= time_delay) {
			if (target != nullptr) {
				Quaternion new_rot =
					get_parent_transform()->look_at_direction(
						target->get_transformed_position(),
						Vector3f{ 0, 0, 1 });

				get_parent_transform()->set_rotation(
					get_parent_transform()
						->get_rotation()
						.slerp(new_rot, delta * 5.0f,
						       true));
			}
			current_delay -= time_delay;
		}
	}

	void input(float delta) override {};
	void render(Shader &) override {};
};
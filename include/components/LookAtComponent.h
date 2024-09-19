#pragma once

#include <graphics/Shader.h>

#include <math/Transform.h>
#include <components/SharedGlobals.h>
#include <components/GameComponent.h>

class LookAtComponent : public GameComponent {
	Transform *target;

    public:
	LookAtComponent(Transform *target = nullptr)
		: target(target)
	{
	}

	void update(float delta) override
	{
		if (target != nullptr) {
			Quaternion newRot =
				get_parent_transform()->look_at_direction(
					target->get_transformed_position(),
					Vector3f(0, 1, 0));

			get_parent_transform()->set_rotation(
				get_parent_transform()->get_rotation().slerp(
					newRot, delta * 5.0f, true));
		}
	}
	void input(float delta) override {};
	void render(Shader &) override {};
};
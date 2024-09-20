#pragma once

#include <math/Vector3f.h>
#include <math/Transform.h>

#include <graphics/Shader.h>

#include <components/SharedGlobals.h>
#include <components/GameComponent.h>

class FollowComponent : public GameComponent {
	Vector3f offset;
	Transform *target;

    public:
	FollowComponent(const Vector3f &offset, Transform *target = nullptr)
		: target(target)
		, offset(offset) {};

	void update(float delta) override
	{
		if (target != nullptr) {
			get_parent_transform()->set_translation(
				target->get_translation() + offset);
		}
	}
	void input(float delta) override {};
	void render(Shader &) override {};
};
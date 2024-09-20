

#pragma once

#include <math/Transform.h>

#include <graphics/Shader.h>

class GameComponent {
	Transform *transform = nullptr;

    public:
	//TODO: update docs

	virtual void input(float delta = 0) = 0;

	virtual void update(float delta = 0) = 0;

	virtual void render(Shader &shader) = 0;

	virtual void reset() {};

	virtual ~GameComponent() = default;

	virtual void add_to_rendering_engine(bool id = 0) {};

	Transform *get_parent_transform() const noexcept
	{
		return transform;
	}

	void set_parent_transform(Transform *transform)
	{
		this->transform = transform;
	}
};

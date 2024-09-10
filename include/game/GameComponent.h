#pragma once

#include <graphics/Shader.h>

#include <math/Transform.h>

class GameComponent {
    public:
	virtual void input(const Transform &transform) = 0;
	virtual void update(const Transform &transform) = 0;
	virtual void render(const Transform &transform, Shader &shader) = 0;
	virtual ~GameComponent() = default;
};
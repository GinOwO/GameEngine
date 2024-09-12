#pragma once

#include <math/Transform.h>

#include <graphics/Shader.h>

class GameComponent {
    public:
	virtual void input(const Transform &transform) = 0;
	virtual void update(const Transform &transform) = 0;
	virtual void render(const Transform &transform, Shader &shader) = 0;
	virtual ~GameComponent() = default;
};
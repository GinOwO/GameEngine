#pragma once

#include <math/Vector3f.h>

class Vertex {
    private:
	Vector3f pos;

    public:
	static const int SIZE = 3;
	Vertex();
	Vertex(const Vector3f &pos);

	Vector3f getPos() const noexcept;
	void setPos(const Vector3f &pos) noexcept;
};
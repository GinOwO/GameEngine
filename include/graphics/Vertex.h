#pragma once

#include <math/Vector2f.h>
#include <math/Vector3f.h>

class Vertex {
    private:
	Vector3f pos;
	Vector3f normal;
	Vector2f texCoord;

    public:
	static const int SIZE = 8;
	Vertex();
	Vertex(const Vector3f &pos);
	Vertex(const Vector3f &pos, const Vector2f &texCoord);
	Vertex(const Vector3f &pos, const Vector2f &texCoord,
	       const Vector3f &normal);

	Vector3f get_pos() const noexcept;
	void set_pos(const Vector3f &pos) noexcept;

	Vector3f get_normal() const noexcept;
	void set_normal(const Vector3f &pos) noexcept;

	Vector2f get_texCoord() const noexcept;
	void set_texCoord(const Vector2f &texCoord) noexcept;
};
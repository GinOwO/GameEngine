#pragma once

#include <math/Vector3f.h>

#include <graphics/Texture.h>

class Material {
	Texture texture;
	Vector3f color;

    public:
	Material();
	Material(const Texture &texture, const Vector3f &color);

	void set_texture(const Texture &texture);
	Texture get_texture() const noexcept;

	void set_color(const Vector3f &color);
	Vector3f get_color() const noexcept;
};
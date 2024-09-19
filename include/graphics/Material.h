#pragma once

#include <math/Vector3f.h>

#include <graphics/Texture.h>
#include <graphics/Specular.h>

class Material {
	Texture texture;
	Vector3f color;
	Specular specular;

    public:
	Material();
	Material(const Texture &texture, const Vector3f &color);
	Material(const Texture &texture, const Vector3f &color,
		 const Specular &specular);

	void set_texture(const Texture &texture);
	Texture get_texture() const noexcept;

	void set_color(const Vector3f &color);
	Vector3f get_color() const noexcept;

	void set_specular(const Specular &specular);
	Specular get_specular() const noexcept;
};
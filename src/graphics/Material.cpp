#include <graphics/Material.h>

#include <graphics/Texture.h>
#include <math/Vector3f.h>

Material::Material()
{
}

Material::Material(const Texture &texture, const Vector3f &color)
{
	this->texture = Texture(texture);
	this->color = Vector3f(color);
}

void Material::set_texture(const Texture &texture)
{
	this->texture = Texture(texture);
}

Texture Material::get_texture() const noexcept
{
	return this->texture;
}

void Material::set_color(const Vector3f &color)
{
	this->color = Vector3f(color);
}

Vector3f Material::get_color() const noexcept
{
	return color;
}
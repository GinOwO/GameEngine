#include <graphics/Material.h>

#include <math/Vector3f.h>

#include <graphics/Texture.h>
#include <graphics/Specular.h>

Material::Material()
{
}

Material::Material(const Texture &texture, const Vector3f &color)
{
	this->texture = Texture(texture);
	this->color = Vector3f(color);
	this->specular = Specular{ 2, 32 };
}

Material::Material(const Texture &texture, const Vector3f &color,
		   const Specular &specular)
{
	this->texture = Texture(texture);
	this->color = Vector3f(color);
	this->specular = Specular(specular);
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

void Material::set_specular(const Specular &specular)
{
	this->specular = Specular(specular);
}

Specular Material::get_specular() const noexcept
{
	return this->specular;
}
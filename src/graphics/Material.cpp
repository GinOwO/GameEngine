#include <graphics/Material.h>

#include <math/Vector3f.h>

#include <graphics/Texture.h>
#include <graphics/Specular.h>

/***************************************************************************
 * @brief Default constructor for Material.
 *
 * Initializes a Material object with default values.
 ***************************************************************************/
Material::Material()
{
}

/***************************************************************************
 * @brief Constructs a Material with a texture and color.
 *
 * Initializes a Material object with the specified texture and color. 
 * The specular component is initialized with default values.
 *
 * @param texture The texture to be applied to the material.
 * @param color The color of the material.
 ***************************************************************************/
Material::Material(const Texture &texture, const Vector3f &color)
{
	this->texture = Texture(texture);
	this->color = Vector3f(color);
	this->specular = Specular{ 2, 32 };
}

/***************************************************************************
 * @brief Constructs a Material with a texture, color, and specular properties.
 *
 * Initializes a Material object with the specified texture, color, and 
 * specular properties.
 *
 * @param texture The texture to be applied to the material.
 * @param color The color of the material.
 * @param specular The specular properties of the material.
 ***************************************************************************/
Material::Material(const Texture &texture, const Vector3f &color,
		   const Specular &specular)
{
	this->texture = Texture(texture);
	this->color = Vector3f(color);
	this->specular = Specular(specular);
}

/***************************************************************************
 * @brief Sets the texture of the material.
 *
 * Updates the material's texture.
 *
 * @param texture The new texture to be applied to the material.
 ***************************************************************************/
void Material::set_texture(const Texture &texture)
{
	this->texture = Texture(texture);
}

/***************************************************************************
 * @brief Gets the texture of the material.
 *
 * @return The texture applied to the material.
 ***************************************************************************/
Texture Material::get_texture() const noexcept
{
	return this->texture;
}

/***************************************************************************
 * @brief Sets the color of the material.
 *
 * Updates the material's color.
 *
 * @param color The new color of the material.
 ***************************************************************************/
void Material::set_color(const Vector3f &color)
{
	this->color = Vector3f(color);
}

/***************************************************************************
 * @brief Gets the color of the material.
 *
 * @return The color of the material.
 ***************************************************************************/
Vector3f Material::get_color() const noexcept
{
	return color;
}

/***************************************************************************
 * @brief Sets the specular properties of the material.
 *
 * Updates the material's specular properties.
 *
 * @param specular The new specular properties of the material.
 ***************************************************************************/
void Material::set_specular(const Specular &specular)
{
	this->specular = Specular(specular);
}

/***************************************************************************
 * @brief Gets the specular properties of the material.
 *
 * @return The specular properties of the material.
 ***************************************************************************/
Specular Material::get_specular() const noexcept
{
	return this->specular;
}

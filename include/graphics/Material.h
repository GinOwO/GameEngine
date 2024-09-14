/***************************************************************************
 * @file Material.h
 *
 * @brief Declares the Material class for material properties.
 *
 * This file contains the declaration of the Material class, which represents
 * the material properties of a 3D object, including its texture, color, and
 * specular properties.
 *
 ***************************************************************************/

#pragma once

#include <math/Vector3f.h>

#include <graphics/Texture.h>
#include <graphics/Specular.h>

/***************************************************************************
 * @class Material
 *
 * @brief Represents material properties for a 3D object.
 *
 * The Material class includes properties for texture, color, and specular
 * attributes. It defines how the material interacts with light.
 *
 ***************************************************************************/
class Material {
	Texture texture; /**< Texture associated with the material. */
	Vector3f color; /**< Color of the material. */
	Specular specular; /**< Specular properties of the material. */

    public:
	Vector3f ambient; // TODO: REMOVE THIS

	Material();
	Material(const Texture &texture, const Vector3f &color);
	Material(const Texture &texture, const Vector3f &color,
		 const Specular &specular);

	/***************************************************************************
	 * @brief Sets the texture of the material.
	 *
	 * @param texture The new texture.
	 ***************************************************************************/
	void set_texture(const Texture &texture);

	/***************************************************************************
	 * @brief Gets the texture of the material.
	 *
	 * @return The texture.
	 ***************************************************************************/
	Texture get_texture() const noexcept;

	/***************************************************************************
	 * @brief Sets the color of the material.
	 *
	 * @param color The new color.
	 ***************************************************************************/
	void set_color(const Vector3f &color);

	/***************************************************************************
	 * @brief Gets the color of the material.
	 *
	 * @return The color.
	 ***************************************************************************/
	Vector3f get_color() const noexcept;

	/***************************************************************************
	 * @brief Sets the specular properties of the material.
	 *
	 * @param specular The new specular properties.
	 ***************************************************************************/
	void set_specular(const Specular &specular);

	/***************************************************************************
	 * @brief Gets the specular properties of the material.
	 *
	 * @return The specular properties.
	 ***************************************************************************/
	Specular get_specular() const noexcept;
};

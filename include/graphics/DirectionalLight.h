/***************************************************************************
 * @file DirectionalLight.h
 *
 * @brief Declares the DirectionalLight struct for directional lighting.
 *
 * This file contains the declaration of the DirectionalLight struct, which
 * represents a directional light source in the scene. It includes properties
 * for the light's base characteristics and direction.
 *
 ***************************************************************************/

#pragma once

#include <math/Vector3f.h>
#include <graphics/BaseLight.h>

/***************************************************************************
 * @struct DirectionalLight
 *
 * @brief Represents a directional light source in the scene.
 *
 * The DirectionalLight struct includes a base light component and a direction
 * vector. The direction vector specifies the direction of the light.
 *
 ***************************************************************************/
struct DirectionalLight {
	BaseLight base_light; /**< The base light properties. */
	Vector3f direction; /**< The direction of the light. */

	/***************************************************************************
	 * @brief Constructs a DirectionalLight with specified base light and direction.
	 *
	 * @param b The base light properties.
	 * @param d The direction of the light.
	 ***************************************************************************/
	DirectionalLight(const BaseLight &b, const Vector3f &d)
		: base_light(b)
		, direction(d.normalize())
	{
	}

	DirectionalLight() = default;

	/***************************************************************************
	 * @brief Sets the direction of the light.
	 *
	 * @param direction The new direction of the light.
	 ***************************************************************************/
	void set_direction(const Vector3f &direction)
	{
		this->direction = direction.normalize();
	}
};

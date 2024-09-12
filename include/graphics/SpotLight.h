/***************************************************************************
 * @file SpotLight.h
 *
 * @brief Declares the SpotLight struct for spot light sources.
 *
 * This file contains the declaration of the SpotLight struct, which represents
 * a spot light source in the scene. It includes properties for the light's
 * point light characteristics, direction, and cutoff angle.
 *
 ***************************************************************************/

#pragma once

#include <math/Vector3f.h>
#include <graphics/PointLight.h>

/***************************************************************************
 * @struct SpotLight
 *
 * @brief Represents a spot light source in the scene.
 *
 * The SpotLight struct includes a point light component, a direction vector,
 * and a cutoff angle. It models a light that shines in a specific direction
 * with a defined cone of illumination.
 *
 ***************************************************************************/
struct SpotLight {
	PointLight
		point_light; /**< The point light component of the spot light. */
	Vector3f direction; /**< The direction of the light. */
	float cutoff; /**< The cutoff angle of the light. */

	SpotLight() = default;

	/***************************************************************************
	 * @brief Constructs a SpotLight with specified properties.
	 *
	 * @param point_light The point light component.
	 * @param direction The direction of the light.
	 * @param cutoff The cutoff angle of the light.
	 ***************************************************************************/
	SpotLight(PointLight point_light, Vector3f direction, float cutoff)
		: point_light(point_light)
		, direction(direction.normalize())
		, cutoff(cutoff)
	{
	}

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

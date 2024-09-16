/***************************************************************************
 * @file PointLight.h
 *
 * @brief Declares the PointLight struct for point light sources.
 *
 * This file contains the declaration of the PointLight struct, which represents
 * a point light source in the scene. It includes properties for the light's
 * base characteristics, attenuation, position, and range.
 *
 ***************************************************************************/

#pragma once

#include <math/Vector3f.h>

#include <graphics/Attenuation.h>

#include <components/BaseLight.h>
#include <components/LightSources.h>

/***************************************************************************
 * @struct PointLight
 *
 * @brief Represents a point light source in the scene.
 *
 * The PointLight struct includes base light properties, attenuation, position,
 * and range. It models a light that radiates from a single point in all directions.
 *
 ***************************************************************************/
struct PointLight : public BaseLight {
	Attenuation attenuation; /**< The light's attenuation properties. */
	Vector3f position; /**< The position of the light. */
	float range; /**< The range of the light. */

	PointLight() = default;

	/***************************************************************************
	 * @brief Constructs a PointLight with specified properties.
	 *
	 * @param base_light The base light properties.
	 * @param attenuation The attenuation properties.
	 * @param position The position of the light.
	 * @param range The range of the light.
	 ***************************************************************************/
	PointLight(const Vector3f &color, const float &intensity,
		   const Attenuation &attenuation, const Vector3f &position,
		   float range)
		: BaseLight(color, intensity)
		, attenuation(attenuation)
		, position(position)
		, range(range)
	{
	}

	// TODO: comments
	void add_to_rendering_engine(bool id) override
	{
		LightSources::get_instance().add_to_point_lights(
			static_cast<void *>(this));
	}
};

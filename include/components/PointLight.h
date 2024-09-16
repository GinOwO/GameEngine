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

#include <graphics/ForwardPoint.h>

#include <components/BaseLight.h>
#include <components/SharedGlobals.h>

#include <string>

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
	PointLight() = default;

	/***************************************************************************
	 * @brief Constructs a PointLight with specified properties.
	 *
	 * Initializes the light color from the given RGB values, normalizing them
	 * to the range [0.0f, 1.0f]. If the RGB values are greater than 1.0, they
	 * are divided by 255.0 to normalize.
	 * 
	 * @param color The color of the light, specified as a Vector3f.
	 * @param intensity The intensity of the light.
	 * @param attenuation The attenuation properties (constant, linear, exponent).
	 ***************************************************************************/
	PointLight(const Vector3f &color, const float &intensity,
		   const Vector3f &attenuation)
		: BaseLight(color, intensity)
	{
		this->attenuation = attenuation;
		this->range = 1000.0f;
		this->shader = &ForwardPoint::get_instance();
	}

	/***************************************************************************
	 * @brief Constructs a PointLight with specified properties.
	 *
	 * Initializes the light color from the given HEX color string. The HEX string
	 * should be in the format "#RRGGBB" or "RRGGBB". Throws an exception if the
	 * HEX string format is invalid.
	 *
	 * @param hex The color of the light, specified as a HEX color string.
	 * @param intensity The intensity of the light.
	 * @param attenuation The attenuation properties.
	 ***************************************************************************/
	PointLight(const std::string &color, const float &intensity,
		   const Vector3f &attenuation)
		: BaseLight(color, intensity)
	{
		this->attenuation = attenuation;
		this->range = 1000.0f;
		this->shader = &ForwardPoint::get_instance();
	}
};

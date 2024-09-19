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

#include <graphics/Attenuation.h>
#include <graphics/ForwardSpot.h>

#include <components/PointLight.h>

#include <string>

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
struct SpotLight : public PointLight {
	SpotLight() = default;

	/***************************************************************************
	 * @brief Constructs a SpotLight with specified properties.
	 *
	 * Initializes the light color from the given RGB values, normalizing them
	 * to the range [0.0f, 1.0f]. If the RGB values are greater than 1.0, they
	 * are divided by 255.0 to normalize.
	 * 
	 * @param color The color of the light, specified as a Vector3f.
	 * @param intensity The intensity of the light.
	 * @param attenuation The attenuation properties.
	 * @param cutoff The cutoff angle of the light.
	 ***************************************************************************/
	SpotLight(const Vector3f &color, const float &intensity,
		  const Attenuation &attenuation, float cutoff)
		: PointLight(color, intensity, attenuation)
	{
		this->cutoff = cutoff;
		this->shader = &ForwardSpot::get_instance();
	}

	/***************************************************************************
	 * @brief Constructs a SpotLight with specified properties.
	 *
	 * Initializes the light color from the given HEX color string. The HEX string
	 * should be in the format "#RRGGBB" or "RRGGBB". Throws an exception if the
	 * HEX string format is invalid.
	 *
	 * @param hex The color of the light, specified as a HEX color string.
	 * @param intensity The intensity of the light.
	 * @param attenuation The attenuation properties (constant, linear, exponent).
	 * @param cutoff The cutoff angle of the light.
	 ***************************************************************************/
	SpotLight(const std::string &hex, const float &intensity,
		  const Attenuation &attenuation, float cutoff)
		: PointLight(hex, intensity, attenuation)
	{
		this->cutoff = cutoff;
		this->shader = &ForwardSpot::get_instance();
	}
};

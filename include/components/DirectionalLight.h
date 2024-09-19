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

#include <graphics/ForwardDirectional.h>

#include <components/BaseLight.h>
#include <components/SharedGlobals.h>

#include <string>

/***************************************************************************
 * @struct DirectionalLight
 *
 * @brief Represents a directional light source in the scene.
 *
 * The DirectionalLight struct includes a base light component and a direction
 * vector. The direction vector specifies the direction of the light.
 *
 ***************************************************************************/
struct DirectionalLight : public BaseLight {
	/***************************************************************************
	 * @brief Constructs a DirectionalLight with specified base light properties and direction.
	 *
	 * Initializes the light color from the given RGB values, normalizing them
	 * to the range [0.0f, 1.0f]. If the RGB values are greater than 1.0, they
	 * are divided by 255.0 to normalize.
	 * 
	 * @param color The color of the light, specified as a Vector3f.
	 * @param intensity The intensity of the light.
	 ***************************************************************************/
	DirectionalLight(const Vector3f &color, const float &intensity)
		: BaseLight(color, intensity)
	{
		shader = &ForwardDirectional::get_instance();
	}

	/***************************************************************************
	 * @brief Constructs a DirectionalLight with specified base light properties and direction.
	 *
	 * Initializes the light color from the given HEX color string. The HEX string
	 * should be in the format "#RRGGBB" or "RRGGBB". Throws an exception if the
	 * HEX string format is invalid.
	 *
	 * @param hex The color of the light, specified as a HEX color string.
	 * @param intensity The intensity of the light.
	 ***************************************************************************/
	DirectionalLight(const std::string &hex, const float &intensity)
		: BaseLight(hex, intensity)
	{
		shader = &ForwardDirectional::get_instance();
	}

	DirectionalLight() = default;
};

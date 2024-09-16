/***************************************************************************
 * @file BaseLight.h
 *
 * @brief Declares the BaseLight struct for representing a basic light source.
 *
 * This file contains the declaration of the BaseLight struct, which represents
 * a light source with color and intensity properties. The light color can be
 * initialized using RGB values or a HEX color string.
 *
 ***************************************************************************/

#pragma once

#include <math/Vector3f.h>

#include <graphics/Attenuation.h>
#include <graphics/Shader.h>

#include <components/GameComponent.h>
#include <components/LightSources.h>

#include <string>
#include <sstream>
#include <iomanip>
#include <exception>

/***************************************************************************
 * @struct BaseLight
 *
 * @brief Represents a basic light source with color and intensity.
 *
 * The BaseLight struct provides a way to define a light source with a color
 * and intensity. The color can be specified using RGB values or a HEX color
 * string. The intensity determines the brightness of the light source.
 *
 ***************************************************************************/
struct BaseLight : public GameComponent {
	// Directional Light
	Vector3f direction; /**< The direction of the light. */

	// Point Light
	Attenuation attenuation; /**< The light's attenuation properties. */
	Vector3f position; /**< The position of the light. */
	float range; /**< The range of the light. */

	/***************************************************************************
	 * @brief The color of the light, represented as a Vector3f.
	 *
	 * The color is normalized to the range [0.0f, 1.0f] based on the input
	 * values.
	 ***************************************************************************/
	Vector3f color;

	/***************************************************************************
	 * @brief The intensity of the light.
	 *
	 * This value represents the brightness of the light source.
	 ***************************************************************************/
	float intensity;

	/***************************************************************************
	 * @brief The shader used to render this BaseLight.
	 *
	 * This object represents the shader used to render this BaseLight.
	 ***************************************************************************/
	Shader *shader;

	/***************************************************************************
	 * @brief Constructs a BaseLight with RGB color and intensity.
	 *
	 * Initializes the light color from the given RGB values, normalizing them
	 * to the range [0.0f, 1.0f]. If the RGB values are greater than 1.0, they
	 * are divided by 255.0 to normalize.
	 *
	 * @param color The color of the light, specified as a Vector3f.
	 * @param intensity The intensity of the light.
	 ***************************************************************************/
	BaseLight(const Vector3f &color, const float &intensity)
		: intensity(intensity)
	{
		float red = color.getX(), green = color.getY(),
		      blue = color.getZ();
		if (red > 1)
			red /= 255.0f;
		if (green > 1)
			green /= 255.0f;
		if (blue > 1)
			blue /= 255.0f;
		this->color = { red, green, blue };
	}

	/***************************************************************************
	 * @brief Constructs a BaseLight with color specified as a HEX string and intensity.
	 *
	 * Initializes the light color from the given HEX color string. The HEX string
	 * should be in the format "#RRGGBB" or "RRGGBB". Throws an exception if the
	 * HEX string format is invalid.
	 *
	 * @param hex The color of the light, specified as a HEX color string.
	 * @param intensity The intensity of the light.
	 *
	 * @throw std::invalid_argument If the HEX color format is invalid.
	 ***************************************************************************/
	BaseLight(const std::string &hex, const float &intensity)
		: intensity(intensity)
	{
		unsigned int red = 0, green = 0, blue = 0;

		std::string hex_value = hex;
		if (hex_value[0] == '#') {
			hex_value = hex_value.substr(1);
		}

		if (hex_value.size() == 3) {
			hex_value = { hex_value[0], hex_value[0], hex_value[1],
				      hex_value[1], hex_value[2], hex_value[2] };
		}

		if (hex_value.size() == 6) {
			std::stringstream ss;
			ss << std::hex << hex_value;
			unsigned int hex_rgb;
			ss >> hex_rgb;
			red = (hex_rgb >> 16) & 0xFF;
			green = (hex_rgb >> 8) & 0xFF;
			blue = hex_rgb & 0xFF;
		} else {
			throw std::invalid_argument("Invalid HEX color format");
		}

		this->color =
			Vector3f(red / 255.0f, green / 255.0f, blue / 255.0f);
	}

	/***************************************************************************
	 * @brief Default constructor for BaseLight.
	 *
	 * Initializes the light color to black and intensity to zero.
	 ***************************************************************************/
	BaseLight()
		: color(0, 0, 0)
		, intensity(0.0f)
	{
	}

    private:
	// TODO: comments
	void input(const Transform &transform) override {};
	void update(const Transform &transform) override {};
	void render(const Transform &transform, Shader &shader) override {};
};

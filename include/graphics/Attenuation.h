/***************************************************************************
 * @file Attenuation.h
 *
 * @brief Declares the Attenuation struct for light attenuation properties.
 *
 * This file contains the declaration of the Attenuation struct, which
 * holds the properties for light attenuation. Attenuation affects how
 * the intensity of a light source decreases with distance.
 *
 ***************************************************************************/

#pragma once

/***************************************************************************
 * @struct Attenuation
 *
 * @brief Represents the attenuation properties of a light source.
 *
 * The Attenuation struct holds three properties that determine how light
 * intensity diminishes with distance: constant, linear, and exponent.
 * These parameters are used in lighting calculations to simulate realistic
 * light falloff.
 *
 ***************************************************************************/
struct Attenuation {
	/***************************************************************************
	 * @brief Linear attenuation factor.
	 *
	 * This value represents the linear component of attenuation, which
	 * decreases the light intensity linearly with distance.
	 ***************************************************************************/
	float linear;

	/***************************************************************************
	 * @brief Constant attenuation factor.
	 *
	 * This value represents the constant component of attenuation, which
	 * affects the light intensity uniformly regardless of distance.
	 ***************************************************************************/
	float constant;

	/***************************************************************************
	 * @brief Exponent attenuation factor.
	 *
	 * This value represents the exponential component of attenuation, which
	 * decreases the light intensity more rapidly with distance.
	 ***************************************************************************/
	float exponent;

	/***************************************************************************
	 * @brief Default constructor for Attenuation.
	 *
	 * Initializes the attenuation factors to default values.
	 ***************************************************************************/
	Attenuation()
	{
	}

	/***************************************************************************
	 * @brief Constructs an Attenuation with specified factors.
	 *
	 * @param constant The constant attenuation factor.
	 * @param linear The linear attenuation factor.
	 * @param exponent The exponential attenuation factor.
	 ***************************************************************************/
	Attenuation(float constant, float linear, float exponent)
		: linear(linear)
		, constant(constant)
		, exponent(exponent)
	{
	}
};

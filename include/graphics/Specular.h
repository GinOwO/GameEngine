/***************************************************************************
 * @file Specular.h
 *
 * @brief Declares the Specular struct for specular lighting properties.
 *
 * This file contains the declaration of the Specular struct, which represents
 * the specular lighting properties, including intensity and exponent.
 *
 ***************************************************************************/

#pragma once

/***************************************************************************
 * @struct Specular
 *
 * @brief Represents specular lighting properties.
 *
 * The Specular struct includes intensity and exponent parameters used in
 * specular lighting calculations.
 *
 ***************************************************************************/
struct Specular {
	float intensity; /**< Intensity of the specular reflection. */
	float exponent; /**< Exponent for the specular reflection. */

	Specular()
		: intensity(0)
		, exponent(0) {};

	/***************************************************************************
	 * @brief Constructs a Specular with specified intensity and exponent.
	 *
	 * @param intensity The intensity of the specular reflection.
	 * @param exponent The exponent of the specular reflection.
	 ***************************************************************************/
	Specular(float intensity, float exponent)
		: intensity(intensity)
		, exponent(exponent) {};
};
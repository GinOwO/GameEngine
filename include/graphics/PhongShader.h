/***************************************************************************
 * @file PhongShader.h
 *
 * @brief Declares the PhongShader class for Phong shading model.
 *
 * This file contains the declaration of the PhongShader class, which extends
 * the Shader class to implement the Phong shading model. It includes methods
 * for loading shaders, updating uniforms, and managing light sources.
 *
 ***************************************************************************/

#pragma once

#include <math/Matrix4f.h>
#include <math/Vector3f.h>

#include <graphics/Shader.h>
#include <graphics/Material.h>
#include <graphics/BaseLight.h>
#include <graphics/SpotLight.h>
#include <graphics/PointLight.h>
#include <graphics/DirectionalLight.h>

#include <vector>
#include <iostream>

/***************************************************************************
 * @class PhongShader
 *
 * @brief Represents a shader that implements the Phong shading model.
 *
 * The PhongShader class provides functionality for implementing the Phong
 * shading model, including support for ambient, directional, point, and
 * spot lights.
 *
 ***************************************************************************/
class PhongShader : public Shader {
    public:
	PhongShader(const PhongShader &) = delete;
	PhongShader &operator=(const PhongShader &) = delete;

	/***************************************************************************
	 * @brief Gets the singleton instance of the PhongShader.
	 *
	 * @return The singleton instance of the PhongShader.
	 ***************************************************************************/
	static PhongShader &get_instance();

    private:
	Vector3f ambient_light{ 0.8, 0.8,
				0.8 }; /**< The ambient light color. */
	DirectionalLight directional_light{
		BaseLight{ "#FFF", 0 },
		{ 0, 0, 0 }
	}; /**< The directional light source. */

	const int MAX_POINT_LIGHTS = 4; /**< Maximum number of point lights. */
	const int MAX_SPOT_LIGHTS = 4; /**< Maximum number of spot lights. */

	PhongShader();

    public:
	std::vector<PointLight> point_lights; /**< List of point lights. */
	std::vector<SpotLight> spot_lights; /**< List of spot lights. */

	/***************************************************************************
	 * @brief Loads the vertex and fragment shaders.
	 ***************************************************************************/
	void load_shader();

	/***************************************************************************
	 * @brief Updates the shader's uniform variables.
	 *
	 * @param transform The transformation matrix to use.
	 * @param material The material properties to use.
	 ***************************************************************************/
	void update_uniforms(const Transform &transform,
			     const Material &material) override;

	/***************************************************************************
	 * @brief Gets the ambient light color.
	 *
	 * @return The ambient light color.
	 ***************************************************************************/
	Vector3f &get_ambient_light() noexcept;

	/***************************************************************************
	 * @brief Sets the ambient light color.
	 *
	 * @param ambient_light The ambient light color to set.
	 ***************************************************************************/
	void set_ambient_light(const Vector3f &ambient_light) noexcept;

	/***************************************************************************
	 * @brief Gets the directional light source.
	 *
	 * @return The directional light source.
	 ***************************************************************************/
	DirectionalLight &get_directional_light() noexcept;

	/***************************************************************************
	 * @brief Sets the directional light source.
	 *
	 * @param directional_light The directional light source to set.
	 ***************************************************************************/
	void set_directional_light(
		const DirectionalLight &directional_light) noexcept;

	/***************************************************************************
	 * @brief Sets the point lights.
	 *
	 * @param point_lights The list of point lights to set.
	 ***************************************************************************/
	void set_point_lights(const std::vector<PointLight> &point_lights);

	/***************************************************************************
	 * @brief Sets the spot lights.
	 *
	 * @param spot_lights The list of spot lights to set.
	 ***************************************************************************/
	void set_spot_lights(const std::vector<SpotLight> &spot_lights);

	using Shader::set_uniform;

	/***************************************************************************
	 * @brief Sets a uniform variable for a BaseLight.
	 *
	 * @param uniform The name of the uniform variable.
	 * @param base_light The BaseLight value to set.
	 ***************************************************************************/
	void set_uniform(const std::string &uniform,
			 const BaseLight &base_light) noexcept;

	/***************************************************************************
	 * @brief Sets a uniform variable for a DirectionalLight.
	 *
	 * @param uniform The name of the uniform variable.
	 * @param directional_light The DirectionalLight value to set.
	 ***************************************************************************/
	void set_uniform(const std::string &uniform,
			 const DirectionalLight &directional_light) noexcept;

	/***************************************************************************
	 * @brief Sets a uniform variable for a PointLight.
	 *
	 * @param uniform The name of the uniform variable.
	 * @param point_light The PointLight value to set.
	 ***************************************************************************/
	void set_uniform(const std::string &uniform,
			 const PointLight &point_light) noexcept;

	/***************************************************************************
	 * @brief Sets a uniform variable for a SpotLight.
	 *
	 * @param uniform The name of the uniform variable.
	 * @param spot_light The SpotLight value to set.
	 ***************************************************************************/
	void set_uniform(const std::string &uniform,
			 const SpotLight &spot_light) noexcept;
};

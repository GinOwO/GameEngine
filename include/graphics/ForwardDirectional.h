/***************************************************************************
 * @file ForwardDirectional.h
 *
 * @brief Declares the ForwardDirectional class for the directional lighting as part of
 * the forward rendering pipeline.
 *
 * This file contains the declaration of the ForwardDirectional class, which extends
 * the Shader class to provide directional lighting as part of the forward rendering
 * pipeline. It includes methods for loading shaders and updating uniforms specific 
 * to basic shading.
 *
 ***************************************************************************/

#pragma once

#include <math/Matrix4f.h>
#include <math/Transform.h>

#include <components/BaseCamera.h>

#include <graphics/Shader.h>
#include <graphics/Material.h>

#include <components/BaseLight.h>

/***************************************************************************
 * @class ForwardDirectional
 *
 * @brief Represents the directional lighting of the forward rendering pipeline
 *
 * The ForwardDirectional class provides functionality for loading and using shaders.
 * It is intended for directional lighting as part of the forward rendering pipeline.
 *
 ***************************************************************************/
class ForwardDirectional : public Shader {
	ForwardDirectional();

    public:
	ForwardDirectional(const ForwardDirectional &) = delete;
	ForwardDirectional &operator=(const ForwardDirectional &) = delete;

	/***************************************************************************
	 * @brief Gets the singleton instance of the ForwardDirectional.
	 *
	 * @return The singleton instance of the ForwardDirectional.
	 ***************************************************************************/
	static ForwardDirectional &get_instance();

	/***************************************************************************
	 * @brief Loads the vertex and fragment shaders.
	 ***************************************************************************/
	void load_shader();

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
	 * @brief Updates the shader's uniform variables.
	 *
	 * @param transform The transformation matrix to use.
	 * @param material The material properties to use.
	 ***************************************************************************/
	void update_uniforms(Transform *transform,
			     const Material &material) override;
};

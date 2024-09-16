/***************************************************************************
 * @file ForwardSpot.h
 *
 * @brief Declares the ForwardSpot class for the spot light lighting as part of
 * the forward rendering pipeline.
 *
 * This file contains the declaration of the ForwardSpot class, which extends
 * the Shader class to provide spot light lighting as part of the forward rendering
 * pipeline. It includes methods for loading shaders and updating uniforms specific 
 * to basic shading.
 *
 ***************************************************************************/

#pragma once

#include <math/Matrix4f.h>
#include <math/Transform.h>

#include <core/Camera.h>

#include <components/BaseLight.h>
#include <graphics/Shader.h>
#include <graphics/Material.h>

/***************************************************************************
 * @class ForwardSpot
 *
 * @brief Represents the spot light lighting of the forward rendering pipeline
 *
 * The ForwardSpot class provides functionality for loading and using shaders.
 * It is intended for spot light lighting as part of the forward rendering pipeline.
 *
 ***************************************************************************/
class ForwardSpot : public Shader {
	ForwardSpot();

    public:
	ForwardSpot(const ForwardSpot &) = delete;
	ForwardSpot &operator=(const ForwardSpot &) = delete;

	/***************************************************************************
	 * @brief Gets the singleton instance of the ForwardSpot.
	 *
	 * @return The singleton instance of the ForwardSpot.
	 ***************************************************************************/
	static ForwardSpot &get_instance();

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
	void update_uniforms(const Transform &transform,
			     const Material &material) override;
};

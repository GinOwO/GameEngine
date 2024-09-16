/***************************************************************************
 * @file ForwardPoint.h
 *
 * @brief Declares the ForwardPoint class for the point light lighting as part of
 * the forward rendering pipeline.
 *
 * This file contains the declaration of the ForwardPoint class, which extends
 * the Shader class to provide point light lighting as part of the forward rendering
 * pipeline. It includes methods for loading shaders and updating uniforms specific 
 * to basic shading.
 *
 ***************************************************************************/

#pragma once

#include <math/Matrix4f.h>
#include <math/Transform.h>

#include <core/Camera.h>

#include <components/BaseLight.h>
#include <components/PointLight.h>
#include <graphics/Shader.h>
#include <graphics/Material.h>

/***************************************************************************
 * @class ForwardPoint
 *
 * @brief Represents the point light lighting of the forward rendering pipeline
 *
 * The ForwardPoint class provides functionality for loading and using shaders.
 * It is intended for point light lighting as part of the forward rendering pipeline.
 *
 ***************************************************************************/
class ForwardPoint : public Shader {
	ForwardPoint();

    public:
	ForwardPoint(const ForwardPoint &) = delete;
	ForwardPoint &operator=(const ForwardPoint &) = delete;

	/***************************************************************************
	 * @brief Gets the singleton instance of the ForwardPoint.
	 *
	 * @return The singleton instance of the ForwardPoint.
	 ***************************************************************************/
	static ForwardPoint &get_instance();

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
	 * @brief Sets a uniform variable for a PointLight.
	 *
	 * @param uniform The name of the uniform variable.
	 * @param point_light The PointLight value to set.
	 ***************************************************************************/
	void set_uniform(const std::string &uniform,
			 const PointLight &point_light) noexcept;

	/***************************************************************************
	 * @brief Updates the shader's uniform variables.
	 *
	 * @param transform The transformation matrix to use.
	 * @param material The material properties to use.
	 ***************************************************************************/
	void update_uniforms(const Transform &transform,
			     const Material &material) override;
};

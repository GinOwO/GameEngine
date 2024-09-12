/***************************************************************************
 * @file BasicShader.h
 *
 * @brief Declares the BasicShader class for basic shader functionality.
 *
 * This file contains the declaration of the BasicShader class, which extends
 * the Shader class to provide basic shader functionality. It includes methods
 * for loading shaders and updating uniforms specific to basic shading.
 *
 ***************************************************************************/

#pragma once

#include <math/Matrix4f.h>
#include <math/Transform.h>

#include <core/Camera.h>

#include <graphics/Shader.h>
#include <graphics/Material.h>

/***************************************************************************
 * @class BasicShader
 *
 * @brief Represents a basic shader for simple shading operations.
 *
 * The BasicShader class provides functionality for loading and using basic
 * shaders. It is intended for simple shading and can be extended for more
 * complex shaders.
 *
 ***************************************************************************/
class BasicShader : public Shader {
	BasicShader();

    public:
	BasicShader(const BasicShader &) = delete;
	BasicShader &operator=(const BasicShader &) = delete;

	/***************************************************************************
	 * @brief Gets the singleton instance of the BasicShader.
	 *
	 * @return The singleton instance of the BasicShader.
	 ***************************************************************************/
	static BasicShader &get_instance();

	/***************************************************************************
	 * @brief Loads the vertex and fragment shaders.
	 *
	 * @param vertex_path Path to the vertex shader file.
	 * @param fragment_path Path to the fragment shader file.
	 ***************************************************************************/
	void load_shader(const std::string &vertex_path,
			 const std::string &fragment_path);

	/***************************************************************************
	 * @brief Updates the shader's uniform variables.
	 *
	 * @param transform The transformation matrix to use.
	 * @param material The material properties to use.
	 ***************************************************************************/
	void update_uniforms(const Transform &transform,
			     const Material &material) override;
};

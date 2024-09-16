/***************************************************************************
 * @file Shader.h
 *
 * @brief Declares the Shader class for managing and using shader programs.
 *
 * This file contains the declaration of the Shader class, which is responsible
 * for creating, managing, and using shader programs. It includes methods for
 * loading shaders, setting uniform variables, and interacting with the GPU.
 *
 ***************************************************************************/

#pragma once

#include <misc/glad.h>
#include <GLFW/glfw3.h>

#include <math/Matrix4f.h>
#include <math/Vector3f.h>
#include <math/Transform.h>

#include <components/BaseCamera.h>

#include <graphics/Material.h>
#include <graphics/Specular.h>

#include <string>
#include <unordered_map>

/***************************************************************************
 * @class Shader
 *
 * @brief Represents a shader program used in graphics rendering.
 *
 * The Shader class manages a shader program, including loading shader source
 * files, creating shader modules, and setting uniform variables. It is
 * designed to be extended by specific shader implementations.
 *
 ***************************************************************************/
class Shader {
    protected:
	Transform const *transform; // TODO: Comment
    private:
	GLuint shader_program; /**< The OpenGL shader program ID. */
	std::unordered_map<std::string, GLuint>
		uniforms; /**< Maps uniform names to their location IDs. */

	/***************************************************************************
	 * @brief Reads the shader source code from a file.
	 *
	 * @param filepath Path to the shader source file.
	 * @return The shader source code as a string.
	 ***************************************************************************/
	std::string read_shader(const std::string &filepath) const;

	/***************************************************************************
	 * @brief Creates a shader module from source code.
	 *
	 * @param shader_source The source code of the shader.
	 * @param module_type The type of shader module (vertex or fragment).
	 * @return The OpenGL shader module ID.
	 ***************************************************************************/
	GLuint create_shader_module(const std::string &shader_source,
				    GLuint module_type) const;

    protected:
	/***************************************************************************
	 * @brief Loads vertex and fragment shaders from files.
	 *
	 * @param vertex_filepath Path to the vertex shader file.
	 * @param fragment_filepath Path to the fragment shader file.
	 ***************************************************************************/
	void load(const std::string &vertex_filepath,
		  const std::string &fragment_filepath);

    public:
	Shader();

	/***************************************************************************
	 * @brief Deletes the shader program.
	 *
	 * This method cleans up the OpenGL resources associated with the shader program.
	 ***************************************************************************/
	void delete_program() noexcept;

	/***************************************************************************
	 * @brief Gets the OpenGL shader program ID.
	 *
	 * @return The OpenGL shader program ID.
	 ***************************************************************************/
	GLuint get_program() const noexcept;

	/***************************************************************************
	 * @brief Activates the shader program for rendering.
	 *
	 * This method sets the shader program as the current one for rendering.
	 ***************************************************************************/
	void use_program() const noexcept;

	/***************************************************************************
	 * @brief Adds a uniform variable to the shader.
	 *
	 * @param uniform The name of the uniform variable.
	 ***************************************************************************/
	void add_uniform(const std::string &uniform);

	/***************************************************************************
	 * @brief Gets the location of a uniform variable.
	 *
	 * @param uniform The name of the uniform variable.
	 * @return The location of the uniform variable.
	 ***************************************************************************/
	GLuint get_uniform(const std::string &uniform) const;

	/***************************************************************************
	 * @brief Sets an integer uniform variable.
	 *
	 * @param uniform The name of the uniform variable.
	 * @param value The integer value to set.
	 ***************************************************************************/
	void set_uniform(const std::string &uniform, int value);

	/***************************************************************************
	 * @brief Sets a floating-point uniform variable.
	 *
	 * @param uniform The name of the uniform variable.
	 * @param value The floating-point value to set.
	 ***************************************************************************/
	void set_uniform(const std::string &uniform, float value);

	/***************************************************************************
	 * @brief Sets a Vector3f uniform variable.
	 *
	 * @param uniform The name of the uniform variable.
	 * @param value The Vector3f value to set.
	 ***************************************************************************/
	void set_uniform(const std::string &uniform, Vector3f value);

	/***************************************************************************
	 * @brief Sets a Matrix4f uniform variable.
	 *
	 * @param uniform The name of the uniform variable.
	 * @param value The Matrix4f value to set.
	 ***************************************************************************/
	void set_uniform(const std::string &uniform, Matrix4f value);

	/***************************************************************************
	 * @brief Sets uniform values for specular lighting.
	 *
	 * Updates the shader uniform for specular lighting, including intensity and 
	 * exponent.
	 *
	 * @param uniform The base name of the uniform.
	 * @param specular The specular lighting data to set.
	 ***************************************************************************/
	void set_uniform(const std::string &uniform, const Specular &specular);

	/***************************************************************************
	 * @brief Updates the shader's uniform variables.
	 *
	 * @param transform The transformation matrix to use.
	 * @param material The material properties to use.
	 ***************************************************************************/
	virtual void update_uniforms(Transform *transform,
				     const Material &material) = 0;
};

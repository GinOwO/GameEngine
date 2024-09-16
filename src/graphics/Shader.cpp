#include <graphics/Shader.h>

#include <misc/glad.h>
#include <GLFW/glfw3.h>

#include <math/Matrix4f.h>
#include <math/Vector3f.h>
#include <math/Transform.h>

#include <components/BaseCamera.h>

#include <graphics/Material.h>
#include <graphics/Specular.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <array>
#include <cstddef>
#include <exception>

// #define _DEBUG_DISPLAY_ALL_UNIFORMS_ON

/***************************************************************************
 * @brief Reads the shader source code from a file.
 *
 * Reads the contents of the specified shader file into a string.
 *
 * @param filepath The path to the shader file.
 * @return The source code of the shader as a string.
 * @throws std::runtime_error if the file does not exist.
 ***************************************************************************/
std::string Shader::read_shader(const std::string &filepath) const
{
	std::ifstream file;
	std::stringstream bufferedLines;
	std::string line;

	file.open(filepath);
	if (!file.good()) {
		std::cerr << "File Does not exist: " << filepath << '\n';
		throw std::runtime_error("File Does not exist");
	}

	while (std::getline(file, line)) {
		bufferedLines << line << '\n';
	}

	file.close();

	std::string source = bufferedLines.str();

	return source;
}

/***************************************************************************
 * @brief Creates a shader module from source code.
 *
 * Compiles a shader from the provided source code and returns the shader module.
 *
 * @param shader_source The source code of the shader.
 * @param module_type The type of shader (e.g., GL_VERTEX_SHADER, GL_FRAGMENT_SHADER).
 * @return The compiled shader module.
 * @throws std::runtime_error if shader compilation fails.
 ***************************************************************************/
GLuint Shader::create_shader_module(const std::string &shader_source,
				    GLuint module_type) const
{
	const char *shader_source_char = shader_source.c_str();
	GLuint shader_module = glCreateShader(module_type);
	glShaderSource(shader_module, 1, &shader_source_char, NULL);
	glCompileShader(shader_module);

	int status;
	glGetShaderiv(shader_module, GL_COMPILE_STATUS, &status);
	if (!status) {
		char error_log[1024];
		glGetShaderInfoLog(shader_module, 1024, NULL, error_log);
		std::cerr << "Error: Shader module compilation error("
			  << module_type << "):\n"
			  << error_log << '\n';
		throw std::runtime_error("Shader module compilation error");
	}
	return shader_module;
}

/***************************************************************************
 * @brief Loads and compiles shaders, and links them into a program.
 *
 * Loads the vertex and fragment shaders from the specified file paths, compiles
 * them, and links them into a shader program.
 *
 * @param vertex_filepath The path to the vertex shader file.
 * @param fragment_filepath The path to the fragment shader file.
 * @throws std::runtime_error if shader linking fails.
 ***************************************************************************/
void Shader::load(const std::string &vertex_filepath,
		  const std::string &fragment_filepath)
{
	std::array<GLuint, 2> modules;
	modules[0] = create_shader_module(read_shader(vertex_filepath),
					  GL_VERTEX_SHADER);
	modules[1] = create_shader_module(read_shader(fragment_filepath),
					  GL_FRAGMENT_SHADER);

	GLuint shader = glCreateProgram();
	for (auto &module : modules) {
		glAttachShader(shader, module);
	}
	glLinkProgram(shader);

	GLint success;
	GLchar infoLog[512];

	glGetProgramiv(shader, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shader, 512, NULL, infoLog);
		std::cerr << "ERROR: Shader linking failed:\n"
			  << infoLog << '\n';
		throw std::runtime_error("Shader linking failed");
	}

	for (auto &module : modules) {
		glDeleteShader(module);
	}

	shader_program = shader;
}

/***************************************************************************
 * @brief Default constructor for Shader.
 *
 * Initializes the Shader object.
 ***************************************************************************/
Shader::Shader()
{
}

/***************************************************************************
 * @brief Gets the ID of the shader program.
 *
 * @return The ID of the shader program.
 ***************************************************************************/
GLuint Shader::get_program() const noexcept
{
	return shader_program;
}

/***************************************************************************
 * @brief Deletes the shader program.
 *
 * Deletes the shader program associated with this Shader object.
 ***************************************************************************/
void Shader::delete_program() noexcept
{
	glDeleteProgram(shader_program);
}

/***************************************************************************
 * @brief Activates the shader program.
 *
 * Makes this shader program the current one for rendering.
 ***************************************************************************/
void Shader::use_program() const noexcept
{
	glUseProgram(shader_program);
}

/***************************************************************************
 * @brief Adds a uniform variable to the shader.
 *
 * Adds a uniform variable to the shader program, allowing it to be set later.
 *
 * @param uniform The name of the uniform variable.
 * @throws std::runtime_error if the uniform could not be added.
 ***************************************************************************/
void Shader::add_uniform(const std::string &uniform)
{
	use_program();
#ifdef _DEBUG_DISPLAY_ALL_UNIFORMS_ON
	GLint numUniforms = 0;
	glGetProgramiv(shader_program, GL_ACTIVE_UNIFORMS, &numUniforms);

	for (GLint i = 0; i < numUniforms; ++i) {
		const GLsizei bufSize = 32;
		GLchar name[bufSize];
		GLsizei length;
		GLint size;
		GLenum type;

		glGetActiveUniform(shader_program, i, bufSize, &length, &size,
				   &type, name);
		std::cout << "Uniform #" << i << ": Name: " << name << '\n';
	}
#endif

	GLuint uniform_location =
		glGetUniformLocation(shader_program, uniform.c_str());

	if (uniform_location == -1) {
		std::cerr << "Error: Couldn't add uniform: \"" << uniform
			  << "\"\n";
		throw std::runtime_error("Couldn't add uniform");
	}

	uniforms[uniform] = uniform_location;
}

/***************************************************************************
 * @brief Gets the location of a uniform variable.
 *
 * Retrieves the location of the specified uniform variable in the shader program.
 *
 * @param uniform The name of the uniform variable.
 * @return The location of the uniform variable.
 * @throws std::runtime_error if the uniform does not exist.
 ***************************************************************************/
GLuint Shader::get_uniform(const std::string &uniform) const
{
	use_program();
	if (!uniforms.count(uniform)) {
		std::cerr << "Error: Uniform Does not exist: \"" << uniform
			  << "\"\n";
		throw std::runtime_error("Uniform Does not exist");
	}
	return uniforms.at(uniform);
}

/***************************************************************************
 * @brief Sets an integer value for a uniform variable.
 *
 * Sets the value of an integer uniform variable in the shader program.
 *
 * @param uniform The name of the uniform variable.
 * @param value The integer value to set.
 * @throws std::runtime_error if the uniform does not exist.
 ***************************************************************************/
void Shader::set_uniform(const std::string &uniform, int value)
{
	use_program();
	if (!uniforms.count(uniform)) {
		std::cerr << "Error: Uniform Does not exist: \"" << uniform
			  << "\"\n";
		throw std::runtime_error("Uniform Does not exist");
	}
	glUniform1i(uniforms[uniform], value);
}

/***************************************************************************
 * @brief Sets a float value for a uniform variable.
 *
 * Sets the value of a float uniform variable in the shader program.
 *
 * @param uniform The name of the uniform variable.
 * @param value The float value to set.
 * @throws std::runtime_error if the uniform does not exist.
 ***************************************************************************/
void Shader::set_uniform(const std::string &uniform, float value)
{
	use_program();
	if (!uniforms.count(uniform)) {
		std::cerr << "Error: Uniform Does not exist: \"" << uniform
			  << "\"\n";
		throw std::runtime_error("Uniform Does not exist");
	}
	glUniform1f(uniforms[uniform], value);
}

/***************************************************************************
 * @brief Sets a Vector3f value for a uniform variable.
 *
 * Sets the value of a Vector3f uniform variable in the shader program.
 *
 * @param uniform The name of the uniform variable.
 * @param vec The Vector3f value to set.
 * @throws std::runtime_error if the uniform does not exist.
 ***************************************************************************/
void Shader::set_uniform(const std::string &uniform, Vector3f vec)
{
	use_program();
	if (!uniforms.count(uniform)) {
		std::cerr << "Error: Uniform Does not exist: \"" << uniform
			  << "\"\n";
		throw std::runtime_error("Uniform Does not exist");
	}
	glUniform3f(uniforms[uniform], vec.getX(), vec.getY(), vec.getZ());
}

/***************************************************************************
 * @brief Sets a Matrix4f value for a uniform variable.
 *
 * Sets the value of a Matrix4f uniform variable in the shader program.
 *
 * @param uniform The name of the uniform variable.
 * @param matrix The Matrix4f value to set.
 * @throws std::runtime_error if the uniform does not exist.
 ***************************************************************************/
void Shader::set_uniform(const std::string &uniform, Matrix4f matrix)
{
	use_program();
	if (!uniforms.count(uniform)) {
		std::cerr << "Error: Uniform Does not exist: \"" << uniform
			  << "\"\n";
		throw std::runtime_error("Uniform Does not exist");
	}
	glUniformMatrix4fv(uniforms[uniform], 1, GL_FALSE, matrix.get_matrix());
}

/***************************************************************************
 * @brief Sets uniform values for specular lighting.
 *
 * Updates the shader uniform for specular lighting, including intensity and 
 * exponent.
 *
 * @param uniform The base name of the uniform.
 * @param specular The specular lighting data to set.
 ***************************************************************************/
void Shader::set_uniform(const std::string &uniform, const Specular &specular)
{
	set_uniform(uniform + ".intensity", specular.intensity);
	set_uniform(uniform + ".exponent", specular.exponent);
}

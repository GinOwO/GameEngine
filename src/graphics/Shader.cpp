#include <graphics/Shader.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <array>
#include <cstddef>

// #define _DEBUG_DISPLAY_ALL_UNIFORMS_ON

std::string Shader::read_shader(const std::string &filepath) const
{
	std::ifstream file;
	std::stringstream bufferedLines;
	std::string line;

	file.open(filepath);
	if (!file.good()) {
		std::cerr << "File Does not exist: " << filepath << '\n';
		exit(EXIT_FAILURE);
	}

	while (std::getline(file, line)) {
		bufferedLines << line << '\n';
	}

	file.close();

	std::string source = bufferedLines.str();

	return source;
}

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
		exit(EXIT_FAILURE);
	}
	return shader_module;
}

Shader::Shader(const std::string &vertex_filepath,
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
		exit(EXIT_FAILURE);
	}

	for (auto &module : modules) {
		glDeleteShader(module);
	}

	shader_program = shader;
}

Shader::Shader()
{
}

GLuint Shader::get_program() const noexcept
{
	return shader_program;
}

void Shader::delete_program() noexcept
{
	glDeleteProgram(shader_program);
}

void Shader::use_program() const noexcept
{
	glUseProgram(shader_program);
}

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
		exit(EXIT_FAILURE);
	}

	uniforms[uniform] = uniform_location;
}

GLuint Shader::get_uniform(const std::string &uniform) const noexcept
{
	use_program();
	if (!uniforms.count(uniform)) {
		std::cerr << "Error: Uniform Does not exist: \"" << uniform
			  << "\"\n";
		exit(EXIT_FAILURE);
	}
	return uniforms.at(uniform);
}

void Shader::set_uniform(const std::string &uniform, int value) noexcept
{
	use_program();
	if (!uniforms.count(uniform)) {
		std::cerr << "Error: Uniform Does not exist: \"" << uniform
			  << "\"\n";
		exit(EXIT_FAILURE);
	}
	glUniform1i(uniforms[uniform], value);
}

void Shader::set_uniform(const std::string &uniform, float value) noexcept
{
	use_program();
	if (!uniforms.count(uniform)) {
		std::cerr << "Error: Uniform Does not exist: \"" << uniform
			  << "\"\n";
		exit(EXIT_FAILURE);
	}
	glUniform1f(uniforms[uniform], value);
}

void Shader::set_uniform(const std::string &uniform, Vector3f vec) noexcept
{
	use_program();
	if (!uniforms.count(uniform)) {
		std::cerr << "Error: Uniform Does not exist: \"" << uniform
			  << "\"\n";
		exit(EXIT_FAILURE);
	}
	glUniform3f(uniforms[uniform], vec.getX(), vec.getY(), vec.getZ());
}

void Shader::set_uniform(const std::string &uniform, Matrix4f matrix) noexcept
{
	use_program();
	if (!uniforms.count(uniform)) {
		std::cerr << "Error: Uniform Does not exist: \"" << uniform
			  << "\"\n";
		exit(EXIT_FAILURE);
	}
	glUniformMatrix4fv(uniforms[uniform], 1, GL_FALSE, matrix.get_matrix());
}
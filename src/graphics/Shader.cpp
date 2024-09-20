#include <graphics/Shader.h>

#include <misc/glad.h>
#include <GLFW/glfw3.h>

#include <math/Matrix4f.h>
#include <math/Vector3f.h>
#include <math/Transform.h>

#include <components/BaseCamera.h>

#include <graphics/Material.h>
#include <graphics/Specular.h>
#include <graphics/resource_management/ShaderResource.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <array>
#include <cstddef>
#include <string>
#include <memory>
#include <unordered_map>
#include <exception>

// #define _DEBUG_DISPLAY_ALL_UNIFORMS_ON
std::unordered_map<std::pair<std::string, std::string>,
		   std::weak_ptr<ShaderResource>, Shader::__pair_hash>
	Shader::shader_cache{};

std::string Shader::read_shader(const std::string &filepath) const
{
	std::ifstream file;
	std::stringstream bufferedLines;
	std::string line;

	file.open(filepath);
	if (!file.good()) {
		std::cerr << "File Does not exist: " << filepath << '\n';
		throw std::runtime_error("File Does not exist");
		throw std::runtime_error("File Does not exist");
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
		throw std::runtime_error("Shader module compilation error");
		throw std::runtime_error("Shader module compilation error");
	}
	return shader_module;
}

void Shader::load(const std::string &vertex_filepath,
		  const std::string &fragment_filepath)
{
	if (shader_cache.count({ vertex_filepath, fragment_filepath })) {
		std::shared_ptr<ShaderResource> resource =
			shader_cache.at({ vertex_filepath, fragment_filepath })
				.lock();
		if (resource) {
			this->shader_resource = resource;
			return;
		}
	}
	if (this->shader_resource == nullptr) {
		shader_resource = std::make_shared<ShaderResource>();
		shader_cache[{ vertex_filepath, fragment_filepath }] =
			shader_resource;
	}

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
		throw std::runtime_error("Shader linking failed");
	}

	for (auto &module : modules) {
		glDeleteShader(module);
	}

	shader_resource->shader_program = shader;
}

Shader::Shader() {};

GLuint Shader::get_program() const noexcept
{
	if (shader_resource == nullptr)
		return 0;
	return shader_resource->shader_program;
}

void Shader::use_program() const noexcept
{
	glUseProgram(shader_resource->shader_program);
}

void Shader::add_uniform(const std::string &uniform)
{
	use_program();
#ifdef _DEBUG_DISPLAY_ALL_UNIFORMS_ON
	GLint numUniforms = 0;
	glGetProgramiv(shader_resource->shader_program, GL_ACTIVE_UNIFORMS,
		       &numUniforms);

	for (GLint i = 0; i < numUniforms; ++i) {
		const GLsizei bufSize = 32;
		GLchar name[bufSize];
		GLsizei length;
		GLint size;
		GLenum type;

		glGetActiveUniform(shader_resource->shader_program, i, bufSize,
				   &length, &size, &type, name);
		std::cout << "Uniform #" << i << ": Name: " << name << '\n';
	}
#endif

	GLuint uniform_location = glGetUniformLocation(
		shader_resource->shader_program, uniform.c_str());

	if (uniform_location == -1) {
		std::cerr << "Error: Couldn't add uniform: \"" << uniform
			  << "\"\n";
		throw std::runtime_error("Couldn't add uniform");
		throw std::runtime_error("Couldn't add uniform");
	}

	shader_resource->uniforms[uniform] = uniform_location;
}

GLuint Shader::get_uniform(const std::string &uniform) const
{
	use_program();
	if (!shader_resource->uniforms.count(uniform)) {
		std::cerr << "Error: Uniform Does not exist: \"" << uniform
			  << "\"\n";
		throw std::runtime_error("Uniform Does not exist");
		throw std::runtime_error("Uniform Does not exist");
	}
	return shader_resource->uniforms.at(uniform);
}

void Shader::set_uniform(const std::string &uniform, int value)
{
	use_program();
	if (!shader_resource->uniforms.count(uniform)) {
		std::cerr << "Error: Uniform Does not exist: \"" << uniform
			  << "\"\n";
		throw std::runtime_error("Uniform Does not exist");
		throw std::runtime_error("Uniform Does not exist");
	}
	glUniform1i(shader_resource->uniforms[uniform], value);
}

void Shader::set_uniform(const std::string &uniform, float value)
{
	use_program();
	if (!shader_resource->uniforms.count(uniform)) {
		std::cerr << "Error: Uniform Does not exist: \"" << uniform
			  << "\"\n";
		throw std::runtime_error("Uniform Does not exist");
		throw std::runtime_error("Uniform Does not exist");
	}
	glUniform1f(shader_resource->uniforms[uniform], value);
}

void Shader::set_uniform(const std::string &uniform, Vector3f vec)
{
	use_program();
	if (!shader_resource->uniforms.count(uniform)) {
		std::cerr << "Error: Uniform Does not exist: \"" << uniform
			  << "\"\n";
		throw std::runtime_error("Uniform Does not exist");
		throw std::runtime_error("Uniform Does not exist");
	}
	glUniform3f(shader_resource->uniforms[uniform], vec.getX(), vec.getY(),
		    vec.getZ());
}

void Shader::set_uniform(const std::string &uniform, Matrix4f matrix)
{
	use_program();
	if (!shader_resource->uniforms.count(uniform)) {
		std::cerr << "Error: Uniform Does not exist: \"" << uniform
			  << "\"\n";
		throw std::runtime_error("Uniform Does not exist");
		throw std::runtime_error("Uniform Does not exist");
	}
	glUniformMatrix4fv(shader_resource->uniforms[uniform], 1, GL_FALSE,
			   matrix.get_matrix());
}

void Shader::set_uniform(const std::string &uniform, const Specular &specular)
{
	set_uniform(uniform + ".intensity", specular.intensity);
	set_uniform(uniform + ".exponent", specular.exponent);
}

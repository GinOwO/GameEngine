#include <shaderIO.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <array>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

std::string read_shader(const std::string &filepath)
{
	std::ifstream file;
	std::stringstream bufferedLines;
	std::string line;

	file.open(filepath);
	while (std::getline(file, line)) {
		bufferedLines << line << '\n';
	}
	file.close();

	std::string source = bufferedLines.str();
	////std::cout << "Source (" << filepath << "):\n" << source << '\n';
	return source;
}

GLuint create_shader_module(const std::string &shader_source,
			    GLuint module_type)
{
	////std::cout << shader_source << '\n';
	const char *shader_source_char = shader_source.c_str();
	GLuint shader_module = glCreateShader(module_type);
	glShaderSource(shader_module, 1, &shader_source_char, NULL);
	glCompileShader(shader_module);

	int status;
	glGetShaderiv(shader_module, GL_COMPILE_STATUS, &status);
	if (!status) {
		char error_log[1024];
		glGetShaderInfoLog(shader_module, 1024, NULL, error_log);
		std::cerr << "Shader module compilation error(" << module_type
			  << "):\n"
			  << error_log << '\n';
		exit(EXIT_FAILURE);
	}
	return shader_module;
}

GLuint create_shader_program(const std::string &vertex_filepath,
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

	for (auto &module : modules) {
		glDeleteShader(module);
	}

	return shader;
}
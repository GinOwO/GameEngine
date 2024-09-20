#pragma once

#include <misc/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <unordered_map>

class ShaderResource {
    public:
	GLuint shader_program;
	std::unordered_map<std::string, GLuint> uniforms;

	ShaderResource();
	~ShaderResource();
};

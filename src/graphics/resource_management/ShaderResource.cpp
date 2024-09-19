#include <graphics/resource_management/ShaderResource.h>

#include <misc/glad.h>
#include <GLFW/glfw3.h>

#include <graphics/Vertex.h>

ShaderResource::ShaderResource()
	: shader_program(0)
	, uniforms{}
{
}

ShaderResource::~ShaderResource()
{
	if (shader_program) {
		glDeleteTextures(1, &shader_program);
		shader_program = 0;
	}
}

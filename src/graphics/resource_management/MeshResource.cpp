#include <graphics/resource_management/MeshResource.h>

#include <misc/glad.h>
#include <GLFW/glfw3.h>

#include <graphics/Vertex.h>

MeshResource::MeshResource()
	: vao(0)
	, vbo(0)
	, ebo(0)
	, size(0)
	, isize(0)
{
}

MeshResource::~MeshResource()
{
	if (ebo) {
		glDeleteBuffers(1, &ebo);
		ebo = 0;
	}
	if (vbo) {
		glDeleteBuffers(size * Vertex::SIZE, &vbo);
		vbo = 0;
	}
	if (vao) {
		glDeleteVertexArrays(1, &vao);
		vao = 0;
	}
}

void MeshResource::init()
{
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);
}
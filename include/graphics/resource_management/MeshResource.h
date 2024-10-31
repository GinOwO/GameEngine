#pragma once

#include <misc/glad.h>
#include <GLFW/glfw3.h>

class MeshResource {
    public:
	GLuint vao;
	GLuint vbo;
	GLuint ebo;

	int32_t size;
	int32_t isize;

	MeshResource();
	~MeshResource();

	void init();
};

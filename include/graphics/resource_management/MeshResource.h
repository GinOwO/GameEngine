#pragma once

#include <misc/glad.h>
#include <GLFW/glfw3.h>

class MeshResource {
    public:
	GLuint vao;
	GLuint vbo;
	GLuint ebo;

	int size;
	int isize;

	MeshResource();
	~MeshResource();

	void init();
};

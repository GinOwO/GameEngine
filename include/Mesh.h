#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Vertex.h>

#include <vector>

class Mesh {
    private:
	GLuint vbo;
	GLuint vao;
	GLuint ebo;
	int size;

    public:
	Mesh();

	void add_vertices(const std::vector<Vertex> &vertices);
	void draw() const;
};
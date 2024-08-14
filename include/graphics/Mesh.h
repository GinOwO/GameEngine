#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <graphics/Vertex.h>

#include <vector>

class Mesh {
    private:
	GLuint vbo;
	GLuint vao;
	GLuint ebo;
	GLuint shader_program;

	int size;

    public:
	Mesh();
	Mesh(const std::vector<Vertex> &vertices, GLuint shader);

	void add_vertices(const std::vector<Vertex> &vertices);
	void set_shader_program(GLuint program);
	void draw() const;
	void delete_mesh();
};
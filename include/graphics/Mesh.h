#pragma once

#include <vector>
#include <string>

#include <misc/glad.h>
#include <GLFW/glfw3.h>

#include <graphics/Vertex.h>
#include <graphics/Shader.h>
#include <graphics/Material.h>

class Mesh {
    private:
	GLuint vao;
	GLuint vbo;
	GLuint ebo;

	int size;
	int isize;

	void calculate_normals(std::vector<Vertex> &vertices,
			       std::vector<int> &indices);

    public:
	Mesh();
	Mesh(const std::vector<Vertex> &vertices,
	     const std::vector<int> &indices, bool normals = false);

	void draw() const;
	void delete_mesh();

	void add_vertices(std::vector<Vertex> vertices,
			  std::vector<int> indices, bool normals = false);

	static Mesh load_mesh(const std::string &file_path);
};
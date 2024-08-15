#pragma once

#include <misc/glad.h>
#include <GLFW/glfw3.h>

#include <graphics/Vertex.h>
#include <graphics/Shader.h>
#include <graphics/Material.h>

#include <vector>
#include <string>

class Mesh {
    private:
	GLuint vao;
	GLuint vbo;
	GLuint ebo;
	Material material;

	int size;
	int isize;

	void calculate_normals(std::vector<Vertex> vertices,
			       std::vector<int> indices);

    public:
	Mesh();
	Mesh(const std::vector<Vertex> &vertices,
	     const std::vector<int> &indices);

	void draw() const;
	void delete_mesh();

	void add_vertices(const std::vector<Vertex> &vertices,
			  const std::vector<int> &indices);

	void set_material(const Material &texture);
	Material &get_material() noexcept;

	static Mesh load_mesh(const std::string &file_path);
};
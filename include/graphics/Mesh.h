#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <graphics/Vertex.h>
#include <graphics/Shader.h>

#include <vector>
#include <string>

class Mesh {
    private:
	GLuint vbo;
	GLuint vao;
	GLuint ebo;
	Shader shader;

	int size;
	int isize;

    public:
	Mesh();
	Mesh(const std::vector<Vertex> &vertices,
	     const std::vector<int> &indices, Shader shader);

	void add_vertices(const std::vector<Vertex> &vertices,
			  const std::vector<int> &indices);
	void set_shader_program(Shader program);
	Shader &get_shader_program() noexcept;
	void draw() const;
	void delete_mesh();

	static Mesh load_mesh(const std::string &file_path);
};
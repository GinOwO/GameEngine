#include <graphics/Mesh.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <graphics/Vertex.h>
#include <graphics/Shader.h>

#include <iostream>
#include <cstdlib>

Mesh::Mesh()
{
	vao = vbo = ebo = size = 0;
}

Mesh::Mesh(const std::vector<Vertex> &vertices, const std::vector<int> &indices,
	   Shader shader_program)
{
	vao = vbo = ebo = size = 0;
	shader = shader_program;
	this->add_vertices(vertices, indices);
}

void Mesh::delete_mesh()
{
	glDeleteBuffers(size * Vertex::SIZE, &vbo);
	glDeleteVertexArrays(1, &vao);
	shader.delete_program();
	vao = vbo = ebo = size = 0;
}

void Mesh::add_vertices(const std::vector<Vertex> &vertices,
			const std::vector<int> &indices)
{
	if (size) {
		std::cerr << "Delete Existing Mesh first\n";
		return;
	}

	size = vertices.size();

	std::vector<float> buffer(size * Vertex::SIZE);

	int i = 0;
	for (const Vertex &v : vertices) {
		Vector3f v3 = v.getPos();
		buffer[i++] = v3.getX();
		buffer[i++] = v3.getY();
		buffer[i++] = v3.getZ();
	}

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, buffer.size() * sizeof(float),
		     buffer.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
			      Vertex::SIZE * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int),
		     indices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Mesh::set_shader_program(Shader shader_program)
{
	shader = shader_program;
}

void Mesh::draw() const
{
	if (vao == 0) {
		std::cerr << "VAO not initialized\n";
		exit(EXIT_FAILURE);
	}

	shader.use_program();

	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

Shader &Mesh::get_shader_program() noexcept
{
	return shader;
}
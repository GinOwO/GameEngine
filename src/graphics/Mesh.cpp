#include <graphics/Mesh.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cstdlib>

Mesh::Mesh()
{
	vao = vbo = ebo = size = shader_program = 0;
}

Mesh::Mesh(const std::vector<Vertex> &vertices, GLuint shader)
{
	vao = vbo = ebo = size = shader_program = 0;
	this->set_shader_program(shader);
	this->add_vertices(vertices);
}

void Mesh::delete_mesh()
{
	glDeleteBuffers(size * Vertex::SIZE, &vbo);
	glDeleteVertexArrays(1, &vao);
	glDeleteShader(shader_program);
	vao = vbo = ebo = size = shader_program = 0;
}

void Mesh::add_vertices(const std::vector<Vertex> &vertices)
{
	if (size) {
		std::cerr << "Delete Existing Mesh first\n";
		return;
	}

	size = vertices.size();

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	std::vector<float> buffer(size * Vertex::SIZE);

	int i = 0;
	for (const Vertex &v : vertices) {
		Vector3f v3 = v.getPos();
		buffer[i++] = v3.getX();
		buffer[i++] = v3.getY();
		buffer[i++] = v3.getZ();
	}

	glBufferData(GL_ARRAY_BUFFER, buffer.size() * sizeof(float),
		     buffer.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
			      (void *)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Mesh::set_shader_program(GLuint program)
{
	shader_program = program;
}

void Mesh::draw() const
{
	if (vao == 0 || shader_program == 0) {
		std::cerr << "VAO or Shader not initialized\n";
		exit(EXIT_FAILURE);
	}

	glUseProgram(shader_program);

	glBindVertexArray(vao);
	if (ebo) {
		glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);
	} else {
		glDrawArrays(GL_TRIANGLES, 0, size);
	}
	glBindVertexArray(0);
}
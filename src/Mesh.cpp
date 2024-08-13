#include <Mesh.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

Mesh::Mesh()
{
	vao = vbo = ebo = size = 0;
}

void Mesh::add_vertices(const std::vector<Vertex> &vertices)
{
	size = vertices.size();
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	double buffer[size * Vertex::SIZE]; // Vertex::SIZE == 3

	int i = 0;
	for (const Vertex &v : vertices) {
		Vector3f v3 = v.getPos();
		buffer[i++] = v3.getX();
		buffer[i++] = v3.getY();
		buffer[i++] = v3.getZ();
	}

	glBufferData(GL_ARRAY_BUFFER, sizeof(buffer), buffer, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 3 * sizeof(double),
			      (void *)0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Mesh::draw() const
{
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, size);
	glBindVertexArray(0);
}
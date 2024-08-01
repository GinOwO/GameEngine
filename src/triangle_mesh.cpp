#include <mesh/triangle_mesh.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>

TriangleMesh::TriangleMesh()
{
	std::vector<float> positions = { -1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f,
					 -1.0f, 1.0f,  0.0f, 1.0f, 1.0f,  0.0f };

	std::vector<GLuint> colorIndices = { 0, 1, 2, 3 };

	std::vector<GLuint> elementIndices = { 0, 1, 2, 2, 1, 3 };

	vertex_count = 4;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	VBO.resize(2);

	glGenBuffers(2, VBO.data());
	glGenBuffers(1, &EBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(float),
		     positions.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 12, (void *)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, colorIndices.size() * sizeof(float),
		     colorIndices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_INT, GL_FALSE, 4, (void *)0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		     elementIndices.size() * sizeof(float),
		     elementIndices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_INT, GL_FALSE, 4, (void *)0);
	glEnableVertexAttribArray(0);
}

TriangleMesh::~TriangleMesh()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(2, VBO.data());
}

void TriangleMesh::draw()
{
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, vertex_count);
}
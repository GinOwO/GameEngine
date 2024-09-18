#pragma once

#include <misc/glad.h>
#include <GLFW/glfw3.h>

// TODO: comment

class MeshResource {
    public:
	GLuint vao; /**< Vertex Array Object. */
	GLuint vbo; /**< Vertex Buffer Object. */
	GLuint ebo; /**< Element Buffer Object. */

	int size; /**< Size of the mesh. */
	int isize; /**< Index size of the mesh. */

	MeshResource();
	~MeshResource();

	void init();
};

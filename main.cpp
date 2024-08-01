#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <shaderIO.h>

#include <iostream>
#include <cstdlib>

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}

int main(int argc, char const *argv[])
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window = glfwCreateWindow(1920, 1080, "test", NULL, NULL);

	if (window == NULL) {
		std::cerr << "Failed to create GLFW window\n";
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Failed to initialize GLAD\n";
		return EXIT_FAILURE;
	}

	GLuint shader = create_shader_program("shaders/vertex.vert",
					      "shaders/fragment.frag");

	float vertices[] = { -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,  -1.0f, -1.0f,
			     0.0f,  0.0f, 0.0f, 1.0f, -1.0f, 0.0f,  1.0f,
			     0.0f,  1.0f, 1.0f, 0.0f, 1.0f,  1.0f };
	unsigned int indices[] = { 0, 1, 2, 2, 3, 0 };

	GLuint VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,
		     GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
		     GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
			      (void *)0);
	glEnableVertexAttribArray(0);
	// TexCoord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
			      (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glClearColor(.25f, .5f, .75f, 1.0f);
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shader);

		// Update uniform values if necessary
		int iResolutionLoc =
			glGetUniformLocation(shader, "iResolution");
		glUniform2f(iResolutionLoc, 800.0f, 600.0f);

		int iTimeLoc = glGetUniformLocation(shader, "iTime");
		glUniform1f(iTimeLoc, (float)glfwGetTime());

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shader);

	glfwDestroyWindow(window);
	glfwTerminate();

	return EXIT_SUCCESS;
}
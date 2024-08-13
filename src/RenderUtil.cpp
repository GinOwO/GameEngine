#include <RenderUtil.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void RenderUtil::clear_screen()
{
	// TODO: Stencil Buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderUtil::init_graphics()
{
	glClearColor(.0f, .0f, .0f, .0f);

	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	// TODO: Depth Clamp

	glEnable(GL_FRAMEBUFFER_SRGB);
}
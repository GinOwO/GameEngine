#include <core/RenderUtil.h>

#include <misc/glad.h>
#include <GLFW/glfw3.h>

#include <math/Vector3f.h>

void RenderUtil::clear_screen()
{
	// TODO: Stencil Buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderUtil::init_graphics()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_DEPTH_CLAMP);
	glEnable(GL_TEXTURE_2D);

	RenderUtil::clear_screen();
}

void RenderUtil::texture_enable(bool enable)
{
	if (enable)
		glEnable(GL_TEXTURE_2D);
	else
		glDisable(GL_TEXTURE_2D);
}

void RenderUtil::set_clear_color(const Vector3f &color)
{
	glClearColor(color.getX(), color.getY(), color.getZ(), 1.0f);
}

void RenderUtil::unbind_textures()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
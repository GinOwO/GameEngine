#include <graphics/RenderingEngine.h>

#include <misc/glad.h>
#include <GLFW/glfw3.h>

#include <graphics/BasicShader.h>

#include <game/GameObject.h>

void RenderingEngine::render(GameObject *object)
{
	clear_screen();
	object->render(BasicShader::get_instance());
}

void RenderingEngine::clear_screen()
{
	// TODO: Stencil Buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

RenderingEngine::RenderingEngine()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_DEPTH_CLAMP);
	glEnable(GL_TEXTURE_2D);

	RenderingEngine::clear_screen();
}

void RenderingEngine::texture_enable(bool enable)
{
	if (enable)
		glEnable(GL_TEXTURE_2D);
	else
		glDisable(GL_TEXTURE_2D);
}

void RenderingEngine::set_clear_color(const Vector3f &color)
{
	glClearColor(color.getX(), color.getY(), color.getZ(), 1.0f);
}

void RenderingEngine::unbind_textures()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

RenderingEngine &RenderingEngine::get_instance()
{
	static RenderingEngine instance;
	return instance;
}
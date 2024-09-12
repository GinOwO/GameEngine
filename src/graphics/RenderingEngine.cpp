#include <graphics/RenderingEngine.h>

#include <misc/glad.h>
#include <GLFW/glfw3.h>

#include <core/Window.h>
#include <core/Camera.h>

#include <graphics/BasicShader.h>

#include <game/GameObject.h>

#include <cmath>

template <typename T> inline float to_radians(T degrees)
{
	return (degrees * M_PI) / 180.0;
}

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
	: camera(Camera::get_instance())
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
	camera.set_projection(
		to_radians(70.0f),
		Window::get_instance().get_window_width() /
			Window::get_instance().get_window_height(),
		.1f, 1000.0f);
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

void RenderingEngine::input()
{
	Camera::get_instance().input();
}
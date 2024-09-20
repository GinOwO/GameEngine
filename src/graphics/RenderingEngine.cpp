#include <graphics/RenderingEngine.h>

#include <misc/glad.h>
#include <GLFW/glfw3.h>

#include <math/Vector3f.h>

#include <core/Window.h>

#include <graphics/ForwardAmbient.h>
#include <graphics/ForwardDirectional.h>
#include <graphics/ForwardPoint.h>
#include <graphics/ForwardSpot.h>

#include <components/BaseCamera.h>
#include <components/BaseLight.h>
#include <components/GameObject.h>
#include <components/SharedGlobals.h>

#include <cmath>

void RenderingEngine::clear_screen()
{
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

void RenderingEngine::input()
{
}

void RenderingEngine::render(GameObject *object)
{
	clear_screen();

	SharedGlobals &light_sources = SharedGlobals::get_instance();

	object->render(ForwardAmbient::get_instance());

	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);
	glDepthMask(GL_FALSE);
	glDepthFunc(GL_EQUAL);

	for (void *light : light_sources.get_lights()) {
		light_sources.active_light = light;
		object->render(*(static_cast<BaseLight *>(light)->shader));
	}

	glDepthFunc(GL_LESS);
	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
}
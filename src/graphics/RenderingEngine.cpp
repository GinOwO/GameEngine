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

/***************************************************************************
 * @brief Clears the screen buffer.
 *
 * Clears the color and depth buffers.
 ***************************************************************************/
void RenderingEngine::clear_screen()
{
	// TODO: Stencil Buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

/***************************************************************************
 * @brief Default constructor for RenderingEngine.
 *
 * Initializes OpenGL settings and sets up the camera projection.
 ***************************************************************************/
RenderingEngine::RenderingEngine()
{
	SharedGlobals::get_instance().active_ambient_light = Vector3f(0.2f);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_DEPTH_CLAMP);
	glEnable(GL_TEXTURE_2D);

	RenderingEngine::clear_screen();
	static_cast<BaseCamera *>(SharedGlobals::get_instance().main_camera)
		->set_projection(
			to_radians(70.0f),
			Window::get_instance().get_window_width() /
				Window::get_instance().get_window_height(),
			.1f, 1000.0f);
}

/***************************************************************************
 * @brief Enables or disables texture mapping.
 *
 * Enables or disables texture mapping based on the provided flag.
 *
 * @param enable True to enable texture mapping, false to disable.
 ***************************************************************************/
void RenderingEngine::texture_enable(bool enable)
{
	if (enable)
		glEnable(GL_TEXTURE_2D);
	else
		glDisable(GL_TEXTURE_2D);
}

/***************************************************************************
 * @brief Sets the clear color for the screen.
 *
 * Sets the color used when clearing the screen.
 *
 * @param color The color to set, represented as a Vector3f.
 ***************************************************************************/
void RenderingEngine::set_clear_color(const Vector3f &color)
{
	glClearColor(color.getX(), color.getY(), color.getZ(), 1.0f);
}

/***************************************************************************
 * @brief Unbinds all textures.
 *
 * Unbinds any currently bound texture by setting the texture unit to 0.
 ***************************************************************************/
void RenderingEngine::unbind_textures()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

/***************************************************************************
 * @brief Gets the singleton instance of RenderingEngine.
 *
 * @return A reference to the singleton RenderingEngine instance.
 ***************************************************************************/
RenderingEngine &RenderingEngine::get_instance()
{
	static RenderingEngine instance;
	return instance;
}

/***************************************************************************
 * @brief Handles input.
 ***************************************************************************/
void RenderingEngine::input()
{
}

/***************************************************************************
 * @brief Renders the specified GameObject.
 *
 * Clears the screen and renders the given GameObject using the BasicShader.
 *
 * @param object Pointer to the GameObject to be rendered.
 ***************************************************************************/
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
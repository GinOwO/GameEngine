#include <graphics/RenderingEngine.h>

#include <misc/glad.h>
#include <GLFW/glfw3.h>

#include <core/Camera.h>
#include <core/Window.h>

#include <graphics/ForwardAmbient.h>

#include <game/GameObject.h>

#include <cmath>

/***************************************************************************
 * @brief Converts degrees to radians.
 *
 * Converts the given angle in degrees to radians.
 *
 * @tparam T The type of the angle in degrees.
 * @param degrees The angle in degrees.
 * @return The angle in radians.
 ***************************************************************************/
template <typename T> inline float to_radians(T degrees)
{
	return (degrees * M_PI) / 180.0;
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
	object->render(ForwardAmbient::get_instance());
}

/***************************************************************************
 * @brief Clears the screen buffer.
 *
 * Clears the color and depth buffers. TODO: Implement stencil buffer clearing.
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
	: camera(Camera::get_instance())
	, ambient_light(0.2f)
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
 * @brief Handles input for the camera.
 *
 * Processes input for the camera, allowing it to respond to user controls.
 ***************************************************************************/
void RenderingEngine::input()
{
	Camera::get_instance().input();
}

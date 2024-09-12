#include <core/Engine.h>

#include <misc/glad.h>
#include <GLFW/glfw3.h>

#include <graphics/Shader.h>
#include <graphics/RenderingEngine.h>

#include <core/Camera.h>
#include <core/Input.h>
#include <core/Timer.h>

#include <game/TestGame.h>

#include <iostream>
#include <algorithm>
#include <exception>
#include <string>

#define _DEBUG_FPS_ON

Input &input_handler = Input::get_instance();
bool paused = false;
bool Engine::created = false;

/***************************************************************************
 * @brief Callback function to handle window focus events.
 *
 * Updates the paused state based on whether the window is focused or not.
 *
 * @param window The GLFW window.
 * @param focused Indicates whether the window is focused (GLFW_TRUE) or not.
 ***************************************************************************/
void handle_window_focus(GLFWwindow *window, int focused)
{
	paused = focused != GLFW_TRUE;
#ifdef _DEBUG_FPS_ON
	std::cout << "Paused: " << paused << '\n';
#endif
}

/***************************************************************************
 * @brief Callback function to handle key events.
 *
 * Passes the key event to the input handler.
 *
 * @param window The GLFW window.
 * @param key The key that was pressed or released.
 * @param scancode The scancode of the key.
 * @param action The action (press, release) associated with the event.
 * @param mods Modifier keys (Shift, Ctrl, etc.) that were held down.
 ***************************************************************************/
void key_callback(GLFWwindow *window, int key, int scancode, int action,
		  int mods)
{
	input_handler.key_callback(key, scancode, action, mods);
}

/***************************************************************************
 * @brief Callback function to handle mouse motion events.
 *
 * Passes the mouse motion event to the input handler.
 *
 * @param window The GLFW window.
 * @param xpos The new x-coordinate of the mouse cursor.
 * @param ypos The new y-coordinate of the mouse cursor.
 ***************************************************************************/
void mouse_motion_callback(GLFWwindow *window, double xpos, double ypos)
{
	input_handler.mouse_motion_callback(xpos, ypos);
}

/***************************************************************************
 * @brief Callback function to handle mouse button events.
 *
 * Passes the mouse button event to the input handler.
 *
 * @param window The GLFW window.
 * @param button The mouse button that was pressed or released.
 * @param action The action (press, release) associated with the event.
 * @param mods Modifier keys (Shift, Ctrl, etc.) that were held down.
 ***************************************************************************/
void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
	input_handler.mouse_button_callback(button, action, mods);
}

/***************************************************************************
 * @brief Callback function to handle mouse scroll events.
 *
 * Passes the mouse scroll event to the input handler.
 *
 * @param window The GLFW window.
 * @param xoffset The scroll offset along the x-axis.
 * @param yoffset The scroll offset along the y-axis.
 ***************************************************************************/
void mouse_scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
	input_handler.mouse_scroll_callback(xoffset, yoffset);
}

/***************************************************************************
 * @brief Constructs an Engine object and initializes GLFW.
 *
 * Throws an exception if GLFW initialization fails or if an engine instance
 * already exists.
 ***************************************************************************/
Engine::Engine()
	: window(Window::get_instance())
{
	if (!glfwInit()) {
		std::cerr << "Error: Failed to initialize GLFW\n";
		throw std::runtime_error("Error: Failed to initialize GLFW\n");
	}
	if (Engine::created) {
		std::cerr << "Error: Engine Already Created\n";
		throw std::runtime_error("Error: Engine Already Created\n");
	}
	paused = false;
	this->running = false;
	Engine::created = true;
}

/***************************************************************************
 * @brief Destroys the Engine object and performs cleanup.
 *
 * Cleans up resources and terminates GLFW.
 ***************************************************************************/
Engine::~Engine()
{
	this->cleanup();
}

/***************************************************************************
 * @brief Runs the main loop of the engine.
 *
 * Handles events, updates the game state, and renders frames. The loop
 * continues until the engine is stopped.
 ***************************************************************************/
void Engine::run()
{
	Timer &timer = Timer::get_instance();
	RenderingEngine &rendering_engine = RenderingEngine::get_instance();
	TestGame game;
	game.init();

	int frames = 0;
	double frame_counter = 0;
	double frame_time = 1.0 / this->FRAME_CAP;

	timer.reset();
	while (this->running) {
		glfwPollEvents();
		if (paused) {
			timer.reset();
			continue;
		}
		bool render_frame = false;

		while (timer.can_render_frame(frame_time)) {
			render_frame = true;
			if (window.should_close()) {
				this->stop();
			}

			game.input();
			rendering_engine.input();
			game.update();

			frame_counter += timer.get_delta_time();

			if (frame_counter >= 1) {
#ifdef _DEBUG_FPS_ON
				std::cout << "FPS: " << frames << ' '
					  << frame_counter << '\n';
#endif
				frames = 0;
				frame_counter = 0;
			}
		}

		if (render_frame) {
			rendering_engine.render(game.get_root_object());
			window.swap_buffers();
			frames++;
		}
	}

	this->cleanup();
}

/***************************************************************************
 * @brief Starts the engine and creates the window.
 *
 * Initializes the window, sets up callbacks, and starts the main loop.
 * Throws an exception if the window creation or context setup fails, or
 * if the engine is already running.
 ***************************************************************************/
void Engine::start()
{
	if (!window.gl_create_window()) {
		std::cerr << "Error: Failed to create window\n";
		throw std::runtime_error("Failed to create window\n");
	}
	if (!window.set_window_context()) {
		std::cerr << "Error: Failed to set window context\n";
		throw std::runtime_error("Failed to set window context\n");
	}
	if (running) {
		std::cerr << "Error: Engine Already Running\n";
		throw std::runtime_error("Engine Already Running\n");
	}

	window.set_key_callback(key_callback);
	window.set_mouse_callback(mouse_motion_callback, mouse_button_callback,
				  mouse_scroll_callback);
	window.set_focus_callback(handle_window_focus);
	running = true;
	this->run();
}

/***************************************************************************
 * @brief Stops the engine from running.
 *
 * Sets the running flag to false, which exits the main loop.
 ***************************************************************************/
void Engine::stop()
{
	running = false;
}

/***************************************************************************
 * @brief Cleans up resources and terminates GLFW.
 *
 * Calls the window's terminate method and terminates GLFW.
 ***************************************************************************/
void Engine::cleanup()
{
	window.terminate_window();
	glfwTerminate();
}

/***************************************************************************
 * @brief Gets the window associated with the engine.
 *
 * @return A reference to the window object.
 ***************************************************************************/
Window &Engine::get_window() const noexcept
{
	return window;
}

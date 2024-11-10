#include <core/Engine.h>

#include <misc/glad.h>
#include <GLFW/glfw3.h>

#include <graphics/Shader.h>
#include <graphics/RenderingEngine.h>

#include <core/Input.h>
#include <core/Timer.h>

#include <components/BaseCamera.h>
#include <core/SharedGlobals.h>

#include <game/TestGame.h>

#include <iostream>
#include <algorithm>
#include <exception>
#include <string>

#ifdef MULTIPLAYER

#include <multiplayer/MM.h>

#endif

#define _DEBUG_FPS_ON 0

Input &input_handler = Input::get_instance();
bool paused = false;
bool Engine::created = false;

void handle_window_focus(GLFWwindow *window, int32_t focused)
{
	paused = focused != GLFW_TRUE;
#if _DEBUG_FPS_ON
	std::cout << "Paused: " << paused << "\r\n";
#endif
}

void key_callback(GLFWwindow *window, int32_t key, int32_t scancode,
		  int32_t action, int32_t mods)
{
	input_handler.key_callback(key, scancode, action, mods);
}

void handle_window_close(GLFWwindow *window)
{
#ifdef MULTIPLAYER
	MatchMaking::get_instance().set_match_running(false);
#endif
}

void mouse_motion_callback(GLFWwindow *window, double xpos, double ypos)
{
	input_handler.mouse_motion_callback(xpos, ypos);
}

void mouse_button_callback(GLFWwindow *window, int32_t button, int32_t action,
			   int32_t mods)
{
	input_handler.mouse_button_callback(button, action, mods);
}

void mouse_scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
	input_handler.mouse_scroll_callback(xoffset, yoffset);
}

Engine::Engine()
	: game(new TestGame())
	, window(Window::get_instance())
{
	if (!glfwInit()) {
		std::cerr << "Error: Failed to initialize GLFW\r\n";
		throw std::runtime_error(
			"Error: Failed to initialize GLFW\r\n");
	}
	if (Engine::created) {
		std::cerr << "Error: Engine Already Created\r\n";
		throw std::runtime_error("Error: Engine Already Created\r\n");
	}
	paused = false;
	this->running = false;
	Engine::created = true;
}

Engine::~Engine()
{
	this->cleanup();
}

void Engine::run()
{
	Timer &timer = Timer::get_instance();
	game->init();
	RenderingEngine &rendering_engine = RenderingEngine::get_instance();
#ifdef MULTIPLAYER
	MatchMaking &MM = MatchMaking::get_instance();
#endif

	int32_t frames = 0;
	double frame_counter = 0;
	double frame_time = 1.0f / this->FRAME_CAP;
	// glfwSwapInterval(0); // Disable Vsync

	timer.reset();

	while (this->running
#ifdef MULTIPLAYER
	       && MM.is_match_running()
#endif
	) {
		glfwPollEvents();
#ifndef MULTIPLAYER
		// if (paused) {
		// 	timer.reset();
		// 	continue;
		// }
#endif
		bool render_frame = false;

		while (timer.can_render_frame(frame_time)) {
			render_frame = true;
			if (window.should_close()) {
				this->stop();
			}

			game->input(frame_time);
			game->update(frame_time);
			SharedGlobals::get_instance().increment_tick();

			frame_counter += timer.get_delta_time();

			if (frame_counter >= 1) {
#if _DEBUG_FPS_ON
				std::cout << "FPS: " << frames << ' '
					  << frame_counter << "\r\n";
#endif
				frames = 0;
				frame_counter = 0;
			}
		}

		if (render_frame) {
			rendering_engine.render(game->get_root_object());
			window.swap_buffers();
			frames++;
		}
	}

	this->cleanup();
}

void Engine::start()
{
	if (!window.gl_create_window()) {
		std::cerr << "Error: Failed to create window\r\n";
		throw std::runtime_error("Failed to create window\r\n");
	}
	if (!window.set_window_context()) {
		std::cerr << "Error: Failed to set window context\r\n";
		throw std::runtime_error("Failed to set window context\r\n");
	}
	if (running) {
		std::cerr << "Error: Engine Already Running\r\n";
		throw std::runtime_error("Engine Already Running\r\n");
	}

	window.set_key_callback(key_callback);
	window.set_mouse_callback(mouse_motion_callback, mouse_button_callback,
				  mouse_scroll_callback);
	window.set_focus_callback(handle_window_focus);
	window.set_close_callback(handle_window_close);
	SharedGlobals::get_instance().window = static_cast<void *>(&window);
	running = true;
	this->run();
}

void Engine::stop()
{
	running = false;
}

void Engine::cleanup()
{
	window.terminate_window();
	glfwTerminate();
}

Window &Engine::get_window() const noexcept
{
	return window;
}

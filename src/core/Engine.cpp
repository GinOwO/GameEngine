#include <core/Engine.h>

#include <misc/glad.h>
#include <GLFW/glfw3.h>

#include <graphics/Shader.h>
#include <graphics/RenderingEngine.h>

#include <core/Input.h>
#include <core/Timer.h>

#include <components/BaseCamera.h>
#include <components/SharedGlobals.h>

#include <game/TestGame.h>

#include <iostream>
#include <algorithm>
#include <exception>
#include <string>

#define _DEBUG_FPS_ON

Input &input_handler = Input::get_instance();
bool paused = false;
bool Engine::created = false;

void handle_window_focus(GLFWwindow *window, int focused)
{
	paused = focused != GLFW_TRUE;
#ifdef _DEBUG_FPS_ON
	std::cout << "Paused: " << paused << '\n';
#endif
}

void key_callback(GLFWwindow *window, int key, int scancode, int action,
		  int mods)
{
	input_handler.key_callback(key, scancode, action, mods);
}

void mouse_motion_callback(GLFWwindow *window, double xpos, double ypos)
{
	input_handler.mouse_motion_callback(xpos, ypos);
}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
	input_handler.mouse_button_callback(button, action, mods);
}

void mouse_scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
	input_handler.mouse_scroll_callback(xoffset, yoffset);
}

Engine::Engine()
	: window(Window::get_instance())
{
	if (!glfwInit()) {
		std::cerr << "Error: Failed to initialize GLFW\n";
		throw std::runtime_error("Error: Failed to initialize GLFW\n");
		throw std::runtime_error("Error: Failed to initialize GLFW\n");
	}
	if (Engine::created) {
		std::cerr << "Error: Engine Already Created\n";
		throw std::runtime_error("Error: Engine Already Created\n");
		throw std::runtime_error("Error: Engine Already Created\n");
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
	TestGame game;
	game.init();
	RenderingEngine &rendering_engine = RenderingEngine::get_instance();

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

			game.input(frame_time);
			game.update(frame_time);

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

void Engine::start()
{
	if (!window.gl_create_window()) {
		std::cerr << "Error: Failed to create window\n";
		throw std::runtime_error("Failed to create window\n");
		throw std::runtime_error("Failed to create window\n");
	}
	if (!window.set_window_context()) {
		std::cerr << "Error: Failed to set window context\n";
		throw std::runtime_error("Failed to set window context\n");
		throw std::runtime_error("Failed to set window context\n");
	}
	if (running) {
		std::cerr << "Error: Engine Already Running\n";
		throw std::runtime_error("Engine Already Running\n");
		throw std::runtime_error("Engine Already Running\n");
	}

	window.set_key_callback(key_callback);
	window.set_mouse_callback(mouse_motion_callback, mouse_button_callback,
				  mouse_scroll_callback);
	window.set_focus_callback(handle_window_focus);
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

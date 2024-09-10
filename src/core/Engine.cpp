#include <core/Engine.h>

#include <misc/glad.h>
#include <GLFW/glfw3.h>

#include <graphics/Shader.h>

#include <core/Timer.h>
#include <core/Input.h>
#include <core/Camera.h>
#include <core/RenderUtil.h>

#include <game/Game.h>

#include <iostream>
#include <algorithm>

// #define _DEBUG_INPUT_ON
#define _DEBUG_FPS_ON

Input input_handler = Input();
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
};

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
{
	if (!glfwInit()) {
		std::cerr << "Error: Failed to initialize GLFW\n";
		exit(EXIT_FAILURE);
	}
	if (Engine::created) {
		std::cerr << "Error: Engine Already Created\n";
		exit(EXIT_FAILURE);
	}
	running = false;
	Engine::created = true;
	this->window = Window();
	paused = false;
}

Engine::~Engine()
{
	this->cleanup();
}

void Engine::run()
{
	Timer timer = Timer();
	Camera camera = Camera();
	Game game = Game(input_handler, window, timer, camera);

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
			game.update();

#ifdef _DEBUG_INPUT_ON
			for (int i = 0; i < input_handler.NUM_KEYS; i++) {
				if (input_handler.is_key_pressed(i))
					std::cout << char(i) << '\n';
			}
#endif
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
			game.render();
			frames++;
		}
	}

	this->cleanup();
}

void Engine::start()
{
	if (!window.gl_create_window()) {
		std::cerr << "Error: Failed to create window\n";
		exit(EXIT_FAILURE);
	}
	if (!window.set_window_context()) {
		std::cerr << "Error: Failed to set window context\n";
		exit(EXIT_FAILURE);
	}
	if (running) {
		std::cerr << "Error: Engine Already Running\n";
		exit(EXIT_FAILURE);
	}
	RenderUtil::init_graphics();

	window.set_key_callback(key_callback);
	window.set_mouse_callback(mouse_motion_callback, mouse_button_callback,
				  mouse_scroll_callback);
	window.set_focus_callback(handle_window_focus);
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

Window Engine::get_window() const noexcept
{
	return window;
}

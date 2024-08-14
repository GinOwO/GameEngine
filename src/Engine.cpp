#include <Engine.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Timer.h>
#include <Input.h>
#include <game/Game.h>
#include <RenderUtil.h>
#include <shaderIO.h>

#include <iostream>

// #define _DEBUG_INPUT_ON
#define _DEBUG_FPS_ON

Input input_handler = Input();

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
		std::cerr << "Failed to initialize GLFW\n";
		exit(EXIT_FAILURE);
	}
	running = false;
	this->window = Window();
}

Engine::~Engine()
{
	this->cleanup();
}

void Engine::run()
{
	Timer timer = Timer();
	Game game = Game(input_handler, window);

	int frames = 0;
	double frame_counter = 0;
	double frame_time = 1.0 / this->FRAME_CAP;

	timer.reset();
	while (this->running) {
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
		}

		frame_counter += timer.get_delta_time();

		if (frame_counter >= 1) {
#ifdef _DEBUG_FPS_ON
			std::cout << "FPS: " << frames << ' ' << frame_counter
				  << '\n';
#endif
			frames = 0;
			frame_counter = 0;
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
		std::cerr << "Failed to create window\n";
		exit(EXIT_FAILURE);
	}
	if (!window.set_window_context()) {
		std::cerr << "Failed to set window context\n";
		exit(EXIT_FAILURE);
	}
	RenderUtil ::init_graphics();

	window.set_key_callback(key_callback);
	window.set_mouse_callback(mouse_motion_callback, mouse_button_callback,
				  mouse_scroll_callback);
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

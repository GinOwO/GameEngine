#include <core/Window.h>

#include <misc/glad.h>
#include <GLFW/glfw3.h>

#include <math/Vector2f.h>

#include <core/Input.h>

#include <core/SharedGlobals.h>
#include <components/BaseCamera.h>

#include <iostream>
#include <cstdlib>
#include <exception>
#include <string>

Window &Window::get_instance()
{
	static Window instance;
	return instance;
}

void framebuffer_size_callback(GLFWwindow *window, int32_t width,
			       int32_t height)
{
	SharedGlobals::get_instance().w_height = height;
	SharedGlobals::get_instance().w_width = width;
	SharedGlobals::get_instance().resized = true;
	glViewport(0, 0, width, height);
}

bool Window::gl_create_window()
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	this->window = glfwCreateWindow(1920, 1080, "Engine", nullptr, nullptr);

	if (window == nullptr) {
		std::cerr << "Failed to create GLFW window\n";
		glfwTerminate();
		return false;
	}

	return true;
}

bool Window::set_window_context()
{
	glfwMakeContextCurrent(this->window);
	glfwSetFramebufferSizeCallback(this->window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Failed to initialize GLAD\n";
		return false;
	}
	return true;
}

void Window::terminate_window()
{
	if (this->window != nullptr) {
		glfwDestroyWindow(this->window);
	}
	this->window = nullptr;
}

bool Window::should_close()
{
	return glfwWindowShouldClose(this->window);
}

void Window::swap_buffers()
{
	glfwSwapBuffers(this->window);
}

void Window::set_key_callback(void (*key_callback)(GLFWwindow *, int32_t,
						   int32_t, int32_t, int32_t))
{
	glfwSetKeyCallback(window, key_callback);
}

void Window::set_mouse_callback(
	void (*mouse_motion_callback)(GLFWwindow *, double, double),
	void (*mouse_button_callback)(GLFWwindow *, int32_t, int32_t, int32_t),
	void (*mouse_scroll_callback)(GLFWwindow *, double, double))
{
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, mouse_motion_callback);
	glfwSetScrollCallback(window, mouse_scroll_callback);
}

void Window::set_focus_callback(void (*handle_window_focus)(GLFWwindow *,
							    int32_t))
{
	glfwSetWindowFocusCallback(window, handle_window_focus);
}

Window::Window()
{
	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW\n";
		throw std::runtime_error("Failed to initialize GLFW\n");
		throw std::runtime_error("Failed to initialize GLFW\n");
	}
	this->window = nullptr;
}

Window::~Window()
{
	this->terminate_window();
}

int32_t Window::get_window_height() const noexcept
{
	int32_t width, height;
	glfwGetWindowSize(window, &width, &height);
	return height;
}

int32_t Window::get_window_width() const noexcept
{
	int32_t width, height;
	glfwGetWindowSize(window, &width, &height);
	return width;
}

Vector2f Window::get_window_center() const noexcept
{
	int32_t width, height;
	glfwGetWindowSize(window, &width, &height);
	return { (float)width / 2.0f, (float)height / 2.0f };
}

void Window::set_mouse_position(double x, double y)
{
	glfwSetCursorPos(window, x, y);
}

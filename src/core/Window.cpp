#include <core/Window.h>

#include <misc/glad.h>
#include <GLFW/glfw3.h>

#include <core/Input.h>

#include <iostream>
#include <cstdlib>
#include <exception>
#include <string>

/***************************************************************************
 * @brief Gets the singleton instance of the Window class.
 *
 * @return A reference to the Window instance.
 ***************************************************************************/
Window &Window::get_instance()
{
	static Window instance;
	return instance;
}

/***************************************************************************
 * @brief Callback function for resizing the framebuffer.
 *
 * @param window The GLFW window that is being resized.
 * @param width The new width of the window.
 * @param height The new height of the window.
 ***************************************************************************/
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}

/***************************************************************************
 * @brief Creates a GLFW window with specified hints.
 *
 * @return True if the window was successfully created, false otherwise.
 ***************************************************************************/
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

/***************************************************************************
 * @brief Sets the OpenGL context for the window and initializes GLAD.
 *
 * @return True if the context was successfully set and GLAD initialized, 
 *         false otherwise.
 ***************************************************************************/
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

/***************************************************************************
 * @brief Terminates the window and cleans up resources.
 ***************************************************************************/
void Window::terminate_window()
{
	if (this->window != nullptr) {
		glfwDestroyWindow(this->window);
	}
	this->window = nullptr;
}

/***************************************************************************
 * @brief Checks if the window should close.
 *
 * @return True if the window should close, false otherwise.
 ***************************************************************************/
bool Window::should_close()
{
	return glfwWindowShouldClose(this->window);
}

/***************************************************************************
 * @brief Swaps the front and back buffers of the window.
 ***************************************************************************/
void Window::swap_buffers()
{
	glfwSwapBuffers(this->window);
}

/***************************************************************************
 * @brief Sets the callback function for key events.
 *
 * @param key_callback The function to call for key events.
 ***************************************************************************/
void Window::set_key_callback(void (*key_callback)(GLFWwindow *, int, int, int,
						   int))
{
	glfwSetKeyCallback(window, key_callback);
}

/***************************************************************************
 * @brief Sets the callback functions for mouse events.
 *
 * @param mouse_motion_callback The function to call for mouse motion events.
 * @param mouse_button_callback The function to call for mouse button events.
 * @param mouse_scroll_callback The function to call for mouse scroll events.
 ***************************************************************************/
void Window::set_mouse_callback(
	void (*mouse_motion_callback)(GLFWwindow *, double, double),
	void (*mouse_button_callback)(GLFWwindow *, int, int, int),
	void (*mouse_scroll_callback)(GLFWwindow *, double, double))
{
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, mouse_motion_callback);
	glfwSetScrollCallback(window, mouse_scroll_callback);
}

/***************************************************************************
 * @brief Sets the callback function for window focus events.
 *
 * @param handle_window_focus The function to call for window focus events.
 ***************************************************************************/
void Window::set_focus_callback(void (*handle_window_focus)(GLFWwindow *, int))
{
	glfwSetWindowFocusCallback(window, handle_window_focus);
}

/***************************************************************************
 * @brief Constructs a Window object and initializes GLFW.
 *
 * Throws an exception if GLFW initialization fails.
 ***************************************************************************/
Window::Window()
{
	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW\n";
		throw std::runtime_error("Failed to initialize GLFW\n");
	}
	this->window = nullptr;
}

/***************************************************************************
 * @brief Destructs the Window object and cleans up resources.
 ***************************************************************************/
Window::~Window()
{
	this->terminate_window();
}

/***************************************************************************
 * @brief Gets the height of the window.
 *
 * @return The height of the window in pixels.
 ***************************************************************************/
int Window::get_window_height() const noexcept
{
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	return height;
}

/***************************************************************************
 * @brief Gets the width of the window.
 *
 * @return The width of the window in pixels.
 ***************************************************************************/
int Window::get_window_width() const noexcept
{
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	return width;
}

/***************************************************************************
 * @brief Sets the position of the cursor in the window.
 *
 * @param x The x-coordinate of the cursor.
 * @param y The y-coordinate of the cursor.
 ***************************************************************************/
void Window::set_mouse_position(double x, double y)
{
	glfwSetCursorPos(window, x, y);
}

/***************************************************************************
 * @file Window.h
 *
 * @brief Declares the Window class for managing GLFW window creation and
 *        handling input events.
 *
 * This file contains the declaration of the Window class, which provides
 * methods for creating and managing a GLFW window, handling input events,
 * and managing window-related operations.
 *
 ***************************************************************************/

#pragma once

#include <misc/glad.h>
#include <GLFW/glfw3.h>

#include <math/Vector2f.h>

#include <core/Input.h>

#include <string>

/***************************************************************************
 * @class Window
 *
 * @brief Singleton class for managing GLFW window creation and input handling.
 *
 * The Window class provides methods for creating and managing a GLFW window,
 * setting up callbacks for input events, and querying window properties.
 *
 ***************************************************************************/
class Window {
    public:
	/***************************************************************************
	 * @brief Deleted copy constructor to prevent copying.
	 ***************************************************************************/
	Window(const Window &) = delete;

	/***************************************************************************
	 * @brief Deleted copy assignment operator to prevent copying.
	 ***************************************************************************/
	Window &operator=(const Window &) = delete;

	/***************************************************************************
	 * @brief Gets the singleton instance of the Window class.
	 *
	 * @return Reference to the singleton Window instance.
	 ***************************************************************************/
	static Window &get_instance();

    private:
	/***************************************************************************
	 * @brief Pointer to the GLFW window instance.
	 ***************************************************************************/
	GLFWwindow *window;

	/***************************************************************************
	 * @brief Private constructor to prevent instantiation outside of the class.
	 ***************************************************************************/
	Window();

    public:
	/***************************************************************************
	 * @brief Destructor to clean up GLFW resources.
	 ***************************************************************************/
	~Window();

	/***************************************************************************
	 * @brief Sets the current OpenGL context to the GLFW window.
	 *
	 * @return True if the context was set successfully, false otherwise.
	 ***************************************************************************/
	bool set_window_context();

	/***************************************************************************
	 * @brief Creates a new GLFW window and initializes OpenGL.
	 *
	 * @return True if the window was created successfully, false otherwise.
	 ***************************************************************************/
	bool gl_create_window();

	/***************************************************************************
	 * @brief Terminates the GLFW window and cleans up resources.
	 ***************************************************************************/
	void terminate_window();

	/***************************************************************************
	 * @brief Checks if the window should be closed.
	 *
	 * @return True if the window should be closed, false otherwise.
	 ***************************************************************************/
	bool should_close();

	/***************************************************************************
	 * @brief Swaps the front and back buffers of the GLFW window.
	 ***************************************************************************/
	void swap_buffers();

	/***************************************************************************
	 * @brief Sets the key callback function for handling key events.
	 *
	 * @param key_callback Function pointer to the key callback function.
	 ***************************************************************************/
	void set_key_callback(void (*key_callback)(GLFWwindow *, int, int, int,
						   int));

	/***************************************************************************
	 * @brief Sets the mouse callback functions for handling mouse events.
	 *
	 * @param mouse_motion_callback Function pointer to the mouse motion callback function.
	 * @param mouse_button_callback Function pointer to the mouse button callback function.
	 * @param mouse_scroll_callback Function pointer to the mouse scroll callback function.
	 ***************************************************************************/
	void set_mouse_callback(
		void (*mouse_motion_callback)(GLFWwindow *, double, double),
		void (*mouse_button_callback)(GLFWwindow *, int, int, int),
		void (*mouse_scroll_callback)(GLFWwindow *, double, double));

	/***************************************************************************
	 * @brief Sets the focus callback function for handling window focus events.
	 *
	 * @param handle_window_focus Function pointer to the focus callback function.
	 ***************************************************************************/
	void set_focus_callback(void (*handle_window_focus)(GLFWwindow *, int));

	/***************************************************************************
	 * @brief Gets the height of the window.
	 *
	 * @return The height of the window in pixels.
	 ***************************************************************************/
	int get_window_height() const noexcept;

	/***************************************************************************
	 * @brief Gets the width of the window.
	 *
	 * @return The width of the window in pixels.
	 ***************************************************************************/
	int get_window_width() const noexcept;

	/***************************************************************************
	 * @brief Gets the relatiev center coordinates of the window.
	 *
	 * @return A vector with the relative center coordinates of the window.
	 ***************************************************************************/
	Vector2f get_window_center() const noexcept;

	/***************************************************************************
	 * @brief Sets the position of the mouse cursor.
	 *
	 * @param x The x-coordinate of the mouse position.
	 * @param y The y-coordinate of the mouse position.
	 ***************************************************************************/
	void set_mouse_position(double x, double y);
};

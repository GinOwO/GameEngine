/***************************************************************************
 * @file Input.h
 *
 * @brief Declares the Input class, including its public and private methods
 *	and member variables.
 *
 * This file contains the declaration of the Input class, which handles
 * input events from the keyboard and mouse. It provides methods to check
 * the state of keys and mouse buttons, as well as to retrieve mouse
 * position and scroll information.
 *
 ***************************************************************************/

#pragma once

#define KB_SIZE 350

/***************************************************************************
 * @class Input
 *
 * @brief Singleton class for managing keyboard and mouse input.
 *
 * The Input class provides a way to check the current state of keyboard
 * keys and mouse buttons. It also offers methods to retrieve mouse
 * position and scroll data. The class uses a singleton pattern to ensure
 * only one instance is used throughout the application.
 *
 ***************************************************************************/
class Input {
    public:
	/***************************************************************************
	 * @brief Deleted copy constructor to prevent copying.
	 ***************************************************************************/
	Input(const Input &) = delete;

	/***************************************************************************
	 * @brief Deleted copy assignment operator to prevent copying.
	 ***************************************************************************/
	Input &operator=(const Input &) = delete;

	/***************************************************************************
	 * @brief Gets the singleton instance of the Input class.
	 *
	 * @return Reference to the singleton Input instance.
	 ***************************************************************************/
	static Input &get_instance();

    private:
	/***************************************************************************
	 * @brief Array to track pressed keys.
	 ***************************************************************************/
	bool pressed_keys[KB_SIZE];

	/***************************************************************************
	 * @brief Array to track keys currently held down.
	 ***************************************************************************/
	bool down_keys[KB_SIZE];

	/***************************************************************************
	 * @brief Array to track keys that have been released.
	 ***************************************************************************/
	bool up_keys[KB_SIZE];

	/***************************************************************************
	 * @brief Array to track mouse buttons that are currently pressed.
	 ***************************************************************************/
	bool mouse_buttons_pressed[8];

	/***************************************************************************
	 * @brief Array to track mouse buttons currently held down.
	 ***************************************************************************/
	bool mouse_buttons_down[8];

	/***************************************************************************
	 * @brief Array to track mouse buttons that have been released.
	 ***************************************************************************/
	bool mouse_buttons_up[8];

	/***************************************************************************
	 * @brief Array to track mouse scroll delta.
	 ***************************************************************************/
	double mouse_scroll_delta[2];

	/***************************************************************************
	 * @brief Array to track mouse scroll position.
	 ***************************************************************************/
	double mouse_scroll[2][2];

	/***************************************************************************
	 * @brief Array to track mouse position delta.
	 ***************************************************************************/
	double mouse_pos_delta[2];

	/***************************************************************************
	 * @brief Array to track mouse position.
	 ***************************************************************************/
	double mouse_pos[2][2];

	/***************************************************************************
	 * @brief Private constructor to prevent instantiation outside of the class.
	 ***************************************************************************/
	Input();

    public:
	/***************************************************************************
	 * @brief Number of keys supported by the Input class.
	 ***************************************************************************/
	const int NUM_KEYS = KB_SIZE;

	/***************************************************************************
	 * @brief Checks if a specific key is pressed.
	 *
	 * @param key_code Key code to check.
	 * @return True if the key is pressed, false otherwise.
	 ***************************************************************************/
	bool is_key_pressed(int key_code) const noexcept;

	/***************************************************************************
	 * @brief Checks if a specific key is currently held down.
	 *
	 * @param key_code Key code to check.
	 * @return True if the key is held down, false otherwise.
	 ***************************************************************************/
	bool is_key_down(int key_code) const noexcept;

	/***************************************************************************
	 * @brief Checks if a specific key has been released.
	 *
	 * @param key_code Key code to check.
	 * @return True if the key has been released, false otherwise.
	 ***************************************************************************/
	bool is_key_up(int key_code) const noexcept;

	/***************************************************************************
	 * @brief Gets the array of currently pressed keys.
	 *
	 * @return Pointer to the array of pressed keys.
	 ***************************************************************************/
	const bool *get_pressed() const noexcept;

	/***************************************************************************
	 * @brief Checks if a specific mouse button is pressed.
	 *
	 * @param mouse_code Mouse button code to check.
	 * @return True if the mouse button is pressed, false otherwise.
	 ***************************************************************************/
	bool is_mouse_pressed(int mouse_code) const noexcept;

	/***************************************************************************
	 * @brief Checks if a specific mouse button is currently held down.
	 *
	 * @param mouse_code Mouse button code to check.
	 * @return True if the mouse button is held down, false otherwise.
	 ***************************************************************************/
	bool is_mouse_down(int mouse_code) const noexcept;

	/***************************************************************************
	 * @brief Checks if a specific mouse button has been released.
	 *
	 * @param mouse_code Mouse button code to check.
	 * @return True if the mouse button has been released, false otherwise.
	 ***************************************************************************/
	bool is_mouse_up(int mouse_code) const noexcept;

	/***************************************************************************
	 * @brief Gets the mouse scroll delta.
	 *
	 * @return Pointer to the array of mouse scroll delta values.
	 ***************************************************************************/
	const double (*get_mouse_scroll() const noexcept)[2];

	/***************************************************************************
	 * @brief Gets the current mouse position.
	 *
	 * @return Pointer to the array of mouse position values.
	 ***************************************************************************/
	const double (*get_mouse_pos() const noexcept)[2];

	/***************************************************************************
	 * @brief Gets the mouse scroll delta.
	 *
	 * @return Pointer to the array of mouse scroll delta values.
	 ***************************************************************************/
	const double *get_mouse_scroll_delta() noexcept;

	/***************************************************************************
	 * @brief Gets the mouse position delta.
	 *
	 * @return Pointer to the array of mouse position delta values.
	 ***************************************************************************/
	const double *get_mouse_pos_delta() noexcept;

	/***************************************************************************
	 * @brief Gets the array of currently pressed mouse buttons.
	 *
	 * @return Pointer to the array of pressed mouse buttons.
	 ***************************************************************************/
	const bool *get_mouse_pressed() const noexcept;

	/***************************************************************************
	 * @brief Callback function for key events.
	 *
	 * @param key Key code of the key event.
	 * @param scancode Scancode of the key event.
	 * @param action Action of the key event.
	 * @param mods Modifier keys for the key event.
	 ***************************************************************************/
	void key_callback(int key, int scancode, int action, int mods);

	/***************************************************************************
	 * @brief Callback function for mouse motion events.
	 *
	 * @param xpos X position of the mouse.
	 * @param ypos Y position of the mouse.
	 ***************************************************************************/
	void mouse_motion_callback(double xpos, double ypos) noexcept;

	/***************************************************************************
	 * @brief Callback function for mouse button events.
	 *
	 * @param button Mouse button code.
	 * @param action Action of the mouse button event.
	 * @param mods Modifier keys for the mouse button event.
	 ***************************************************************************/
	void mouse_button_callback(int button, int action, int mods) noexcept;

	/***************************************************************************
	 * @brief Callback function for mouse scroll events.
	 *
	 * @param xoffset X offset of the mouse scroll.
	 * @param yoffset Y offset of the mouse scroll.
	 ***************************************************************************/
	void mouse_scroll_callback(double xoffset, double yoffset) noexcept;
};

#undef KB_SIZE

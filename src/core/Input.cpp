#include <core/Input.h>

// #define _DEBUG_INPUT_ON

#include <misc/glad.h>
#include <GLFW/glfw3.h>

#include <cstring>

#ifdef _DEBUG_INPUT_ON
#include <iostream>
#endif

/***************************************************************************
 * @brief Gets the singleton instance of the Input class.
 *
 * @return A reference to the Input instance.
 ***************************************************************************/
Input &Input::get_instance()
{
	static Input instance;
	return instance;
}

/***************************************************************************
 * @brief Constructs an Input object and initializes member variables.
 ***************************************************************************/
Input::Input()
{
	std::memset(pressed_keys, 0, sizeof(pressed_keys));
	std::memset(down_keys, 0, sizeof(down_keys));
	std::memset(up_keys, 0, sizeof(up_keys));
}

/***************************************************************************
 * @brief Checks if a key is currently pressed.
 *
 * @param key_code The key code to check.
 * @return True if the key is pressed, false otherwise.
 ***************************************************************************/
bool Input::is_key_pressed(int key_code) const noexcept
{
	return pressed_keys[key_code];
}

/***************************************************************************
 * @brief Checks if a key is currently down.
 *
 * @param key_code The key code to check.
 * @return True if the key is down, false otherwise.
 ***************************************************************************/
bool Input::is_key_down(int key_code) const noexcept
{
	return down_keys[key_code];
}

/***************************************************************************
 * @brief Checks if a key was released.
 *
 * @param key_code The key code to check.
 * @return True if the key was released, false otherwise.
 ***************************************************************************/
bool Input::is_key_up(int key_code) const noexcept
{
	return up_keys[key_code];
}

/***************************************************************************
 * @brief Handles key events.
 *
 * Updates the state of the keys based on the key event.
 *
 * @param key The key that was pressed or released.
 * @param scancode The scancode of the key.
 * @param action The action (press, release) associated with the event.
 * @param mods Modifier keys (Shift, Ctrl, etc.) that were held down.
 ***************************************************************************/
void Input::key_callback(int key, int scancode, int action, int mods)
{
	if (key >= 0 && key < NUM_KEYS) {
		if (action == GLFW_PRESS) {
			pressed_keys[key] = true;
			down_keys[key] = true;
		} else if (action == GLFW_RELEASE) {
			pressed_keys[key] = false;
			up_keys[key] = true;
			down_keys[key] = false;
		}
	}
}

/***************************************************************************
 * @brief Handles mouse motion events.
 *
 * Updates the mouse position.
 *
 * @param xpos The new x-coordinate of the mouse cursor.
 * @param ypos The new y-coordinate of the mouse cursor.
 ***************************************************************************/
void Input::mouse_motion_callback(double xpos, double ypos) noexcept
{
	mouse_pos[0][0] = mouse_pos[1][0];
	mouse_pos[0][1] = mouse_pos[1][1];

	mouse_pos[1][0] = xpos;
	mouse_pos[1][1] = ypos;

#ifdef _DEBUG_INPUT_ON
	std::cout << mouse_pos[0][0] << ' ' << mouse_pos[0][1] << ' '
		  << mouse_pos[1][0] << ' ' << mouse_pos[1][1] << '\n';
#endif
}

/***************************************************************************
 * @brief Handles mouse button events.
 *
 * Updates the state of the mouse buttons based on the mouse event.
 *
 * @param button The mouse button that was pressed or released.
 * @param action The action (press, release) associated with the event.
 * @param mods Modifier keys (Shift, Ctrl, etc.) that were held down.
 ***************************************************************************/
void Input::mouse_button_callback(int button, int action, int mods) noexcept
{
	mouse_buttons_pressed[button] = false;
	if (action == GLFW_PRESS && mouse_buttons_down[button]) {
		mouse_buttons_pressed[button] = true;
	}

	mouse_buttons_up[button] = mouse_buttons_down[button] = false;

	if (action == GLFW_PRESS) {
		mouse_buttons_down[button] = true;
#ifdef _DEBUG_INPUT_ON
		std::cout << button << '\n';
#endif
	} else if (action == GLFW_RELEASE) {
		mouse_buttons_up[button] = true;
	}
}

/***************************************************************************
 * @brief Handles mouse scroll events.
 *
 * Updates the mouse scroll delta.
 *
 * @param xoffset The scroll offset along the x-axis.
 * @param yoffset The scroll offset along the y-axis.
 ***************************************************************************/
void Input::mouse_scroll_callback(double xoffset, double yoffset) noexcept
{
	mouse_scroll[0][0] = mouse_scroll[1][0];
	mouse_scroll[0][1] = mouse_scroll[1][1];

	mouse_scroll[1][0] += xoffset;
	mouse_scroll[1][1] += yoffset;

#ifdef _DEBUG_INPUT_ON
	std::cout << mouse_scroll[1][0] << ' ' << mouse_scroll[1][1] << '\n';
#endif
}

/***************************************************************************
 * @brief Gets the state of all pressed keys.
 *
 * @return A pointer to an array of boolean values indicating the pressed state of each key.
 ***************************************************************************/
const bool *Input::get_pressed() const noexcept
{
	return pressed_keys;
}

/***************************************************************************
 * @brief Checks if a mouse button is currently pressed.
 *
 * @param mouse_code The mouse button code to check.
 * @return True if the mouse button is pressed, false otherwise.
 ***************************************************************************/
bool Input::is_mouse_pressed(int mouse_code) const noexcept
{
	return mouse_buttons_pressed[mouse_code];
}

/***************************************************************************
 * @brief Checks if a mouse button is currently down.
 *
 * @param mouse_code The mouse button code to check.
 * @return True if the mouse button is down, false otherwise.
 ***************************************************************************/
bool Input::is_mouse_down(int mouse_code) const noexcept
{
	return mouse_buttons_down[mouse_code];
}

/***************************************************************************
 * @brief Checks if a mouse button was released.
 *
 * @param mouse_code The mouse button code to check.
 * @return True if the mouse button was released, false otherwise.
 ***************************************************************************/
bool Input::is_mouse_up(int mouse_code) const noexcept
{
	return mouse_buttons_up[mouse_code];
}

/***************************************************************************
 * @brief Gets the current mouse scroll offsets.
 *
 * @return A pointer to a 2D array of doubles representing the mouse scroll offsets.
 ***************************************************************************/
const double (*Input::get_mouse_scroll() const noexcept)[2]
{
	return mouse_scroll;
}

/***************************************************************************
 * @brief Gets the current mouse positions.
 *
 * @return A pointer to a 2D array of doubles representing the mouse positions.
 ***************************************************************************/
const double (*Input::get_mouse_pos() const noexcept)[2]
{
	return mouse_pos;
}

/***************************************************************************
 * @brief Gets the state of all mouse buttons.
 *
 * @return A pointer to an array of boolean values indicating the pressed state of each mouse button.
 ***************************************************************************/
const bool *Input::get_mouse_pressed() const noexcept
{
	return mouse_buttons_pressed;
}

/***************************************************************************
 * @brief Calculates and gets the delta of the mouse position.
 *
 * @return A pointer to an array of doubles representing the delta of the mouse position.
 ***************************************************************************/
const double *Input::get_mouse_pos_delta() noexcept
{
	mouse_pos_delta[0] = mouse_pos[1][0] - mouse_pos[0][0];
	mouse_pos_delta[1] = mouse_pos[1][1] - mouse_pos[0][1];

	mouse_pos[0][0] = mouse_pos[1][0];
	mouse_pos[0][1] = mouse_pos[1][1];
	return mouse_pos_delta;
}

/***************************************************************************
 * @brief Calculates and gets the delta of the mouse scroll.
 *
 * @return A pointer to an array of doubles representing the delta of the mouse scroll.
 ***************************************************************************/
const double *Input::get_mouse_scroll_delta() noexcept
{
	mouse_scroll_delta[0] = mouse_scroll[1][0] - mouse_scroll[0][0];
	mouse_scroll_delta[1] = mouse_scroll[1][1] - mouse_scroll[0][1];

	mouse_scroll[0][0] = mouse_scroll[1][0];
	mouse_scroll[0][1] = mouse_scroll[1][1];
	return mouse_scroll_delta;
}

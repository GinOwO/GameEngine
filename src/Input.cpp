#include <Input.h>

// #define _DEBUG_INPUT_ON

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cstring>

#ifdef _DEBUG_INPUT_ON
#include <iostream>
#endif

Input::Input()
{
	std::memset(pressed_keys, 0, sizeof(pressed_keys));
	std::memset(down_keys, 0, sizeof(down_keys));
	std::memset(up_keys, 0, sizeof(up_keys));
}

bool Input::is_key_pressed(int key_code) const noexcept
{
	return pressed_keys[key_code];
}

bool Input::is_key_down(int key_code) const noexcept
{
	return down_keys[key_code];
}

bool Input::is_key_up(int key_code) const noexcept
{
	return up_keys[key_code];
}

void Input::key_callback(int key, int scancode, int action, int mods)
{
	if (key >= 0 && key < NUM_KEYS) {
		pressed_keys[key] = false;
		if (down_keys[key] && action == GLFW_PRESS) {
			pressed_keys[key] = true;
		}

		down_keys[key] = up_keys[key] = false;
		if (action == GLFW_PRESS) {
			down_keys[key] = true;
		} else if (action == GLFW_RELEASE) {
			up_keys[key] = true;
		}
	}
}

void Input::mouse_motion_callback(double xpos, double ypos) noexcept
{
	mouse_pos[0] = xpos;
	mouse_pos[1] = ypos;

#ifdef _DEBUG_INPUT_ON
	std::cout << mouse_pos[0] << ' ' << mouse_pos[1] << '\n';
#endif
}

void Input::mouse_button_callback(int button, int action, int mods) noexcept
{
	mouse_buttons_press[button] = false;
	if (action == GLFW_PRESS && mouse_buttons_down[button]) {
		mouse_buttons_press[button] = true;
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

void Input::mouse_scroll_callback(double xoffset, double yoffset) noexcept
{
	mouse_scroll[0] += xoffset;
	mouse_scroll[1] += yoffset;
#ifdef _DEBUG_INPUT_ON
	std::cout << mouse_scroll[1] << '\n';
#endif
}

const bool *Input::get_pressed() const noexcept
{
	return pressed_keys;
}
#include <core/Input.h>

// #define _DEBUG_INPUT_ON

#include <cstring>

#include <misc/glad.h>
#include <GLFW/glfw3.h>

#ifdef _DEBUG_INPUT_ON
#include <iostream>
#endif

Input &Input::get_instance()
{
	static Input instance;
	return instance;
}

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

void Input::mouse_motion_callback(double xpos, double ypos) noexcept
{
	mouse_pos[0][0] = mouse_pos[1][0];
	mouse_pos[0][1] = mouse_pos[1][1];

	mouse_pos[1][0] = xpos;
	mouse_pos[1][1] = ypos;

#ifdef _DEBUG_INPUT_ON
	std::cout << mouse_pos[0] << ' ' << mouse_pos[1] << '\n';
#endif
}

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

void Input::mouse_scroll_callback(double xoffset, double yoffset) noexcept
{
	mouse_scroll[0][0] = mouse_scroll[1][0];
	mouse_scroll[0][1] = mouse_scroll[1][1];

	mouse_scroll[1][0] += xoffset;
	mouse_scroll[1][1] += yoffset;

#ifdef _DEBUG_INPUT_ON
	std::cout << mouse_scroll[1] << '\n';
#endif
}

const bool *Input::get_pressed() const noexcept
{
	return pressed_keys;
}

bool Input::is_mouse_pressed(int mouse_code) const noexcept
{
	return mouse_buttons_pressed[mouse_code];
}

bool Input::is_mouse_down(int mouse_code) const noexcept
{
	return mouse_buttons_down[mouse_code];
}

bool Input::is_mouse_up(int mouse_code) const noexcept
{
	return mouse_buttons_up[mouse_code];
}

const double (*Input::get_mouse_scroll() const noexcept)[2]
{
	return mouse_scroll;
}

const double (*Input::get_mouse_pos() const noexcept)[2]
{
	return mouse_pos;
}

const bool *Input::get_mouse_pressed() const noexcept
{
	return mouse_buttons_pressed;
}

const double *Input::get_mouse_pos_delta() noexcept
{
	mouse_pos_delta[0] = mouse_pos[1][0] - mouse_pos[0][0];
	mouse_pos_delta[1] = mouse_pos[1][1] - mouse_pos[0][1];

	mouse_pos[0][0] = mouse_pos[1][0];
	mouse_pos[0][1] = mouse_pos[1][1];
	return mouse_pos_delta;
}

const double *Input::get_mouse_scroll_delta() noexcept
{
	mouse_scroll_delta[0] = mouse_scroll[1][0] - mouse_scroll[0][0];
	mouse_scroll_delta[1] = mouse_scroll[1][1] - mouse_scroll[0][1];

	mouse_scroll[0][0] = mouse_scroll[1][0];
	mouse_scroll[0][1] = mouse_scroll[1][1];
	return mouse_scroll_delta;
}
#pragma once

#include <cstdint>

#define KB_SIZE 350

class Input {
    public:
	Input(const Input &) = delete;

	Input &operator=(const Input &) = delete;

	static Input &get_instance();

    private:
	bool pressed_keys[KB_SIZE];

	bool down_keys[KB_SIZE];

	bool up_keys[KB_SIZE];

	bool mouse_buttons_pressed[8];

	bool mouse_buttons_down[8];

	bool mouse_buttons_up[8];

	double mouse_scroll_delta[2];

	double mouse_scroll[2][2];

	double mouse_pos_delta[2];

	double mouse_pos[2][2];

	Input();

    public:
	const int32_t NUM_KEYS = KB_SIZE;

	bool is_key_pressed(int32_t key_code) const noexcept;

	bool is_key_down(int32_t key_code) const noexcept;

	bool is_key_up(int32_t key_code) const noexcept;

	const bool *get_pressed() const noexcept;

	bool is_mouse_pressed(int32_t mouse_code) const noexcept;

	bool is_mouse_down(int32_t mouse_code) const noexcept;

	bool is_mouse_up(int32_t mouse_code) const noexcept;

	const double (*get_mouse_scroll() const noexcept)[2];

	const double (*get_mouse_pos() const noexcept)[2];

	const double *get_mouse_scroll_delta() noexcept;

	const double *get_mouse_pos_delta() noexcept;

	const bool *get_mouse_pressed() const noexcept;

	void key_callback(int32_t key, int32_t scancode, int32_t action,
			  int32_t mods);

	void mouse_motion_callback(double xpos, double ypos) noexcept;

	void mouse_button_callback(int32_t button, int32_t action,
				   int32_t mods) noexcept;

	void mouse_scroll_callback(double xoffset, double yoffset) noexcept;
};

#undef KB_SIZE

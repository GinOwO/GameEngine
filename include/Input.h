#pragma once

#define KB_SIZE 350

class Input {
    private:
	bool pressed_keys[KB_SIZE];
	bool down_keys[KB_SIZE];
	bool up_keys[KB_SIZE];
	bool mouse_buttons_press[8];
	bool mouse_buttons_down[8];
	bool mouse_buttons_up[8];
	double mouse_scroll[2];
	double mouse_pos[2];

    public:
	const int NUM_KEYS = KB_SIZE;

	Input();
	bool is_key_pressed(int key_code) const noexcept;
	bool is_key_down(int key_code) const noexcept;
	bool is_key_up(int key_code) const noexcept;
	const bool *get_pressed() const noexcept;

	void key_callback(int key, int scancode, int action, int mods);
	void mouse_motion_callback(double xpos, double ypos) noexcept;
	void mouse_button_callback(int button, int action, int mods) noexcept;
	void mouse_scroll_callback(double xoffset, double yoffset) noexcept;
};

#undef KB_SIZE
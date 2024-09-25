#pragma once

#include <misc/glad.h>
#include <GLFW/glfw3.h>

#include <core/Input.h>

#include <components/GameComponent.h>

#include <iostream>

class FreeLook : public GameComponent {
	const Vector3f y_axis{ 0, 1, 0 };

	float sensitivity_x, sensitivity_y;
	bool toggled = false;
	double toggle_delay = 0;

    public:
	FreeLook(float sensitivity)
		: sensitivity_x(sensitivity)
		, sensitivity_y(sensitivity) {};
	FreeLook(float sensitivity_x, float sensitivity_y)
		: sensitivity_x(sensitivity_x)
		, sensitivity_y(sensitivity_y) {};

	Vector3f get_forward() const noexcept
	{
		return get_parent_transform()->get_rotation().get_forward();
	}

	Vector3f get_up() const noexcept
	{
		return get_parent_transform()->get_rotation().get_up();
	}

	Vector3f get_left() const noexcept
	{
		return get_parent_transform()->get_rotation().get_left();
	}

	Vector3f get_right() const noexcept
	{
		return get_parent_transform()->get_rotation().get_right();
	}

	void input(float delta) override
	{
		Input &input_handler = Input::get_instance();

		if (toggle_delay > 0) {
			toggle_delay -= delta;
			return;
		}

		if (input_handler.is_key_down(GLFW_KEY_ESCAPE)) {
			toggled = !toggled;
			toggle_delay = .150f; // Reaction time
			return;
		}

		if (!toggled)
			return;

		float rotate_sensitivity = 100.0f * delta;

		const double *m_delta = input_handler.get_mouse_pos_delta();
		float dx = m_delta[0], dy = m_delta[1];

		if (dx != 0) {
			get_parent_transform()->rotate(
				get_forward(),
				to_radians(-dx * rotate_sensitivity *
					   sensitivity_x));
		}
		if (dy != 0) {
			get_parent_transform()->rotate(
				get_right(),
				to_radians(dy * rotate_sensitivity *
					   sensitivity_y));
		}
		if (input_handler.is_mouse_down(GLFW_MOUSE_BUTTON_3)) {
			if (dx != 0) {
				get_parent_transform()->rotate(
					get_up(),
					to_radians(-dx * rotate_sensitivity *
						   sensitivity_x));
			}
		}
	}

	void update(float) override {};
	void render(Shader &) override {};
};
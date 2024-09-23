#pragma once

#include <misc/glad.h>
#include <GLFW/glfw3.h>

#include <core/Input.h>

#include <components/GameComponent.h>

class FreeMove : public GameComponent {
	const Vector3f y_axis{ 0, 1, 0 };

	float sensitivity_x, sensitivity_y, sensitivity_z;

    public:
	FreeMove(float sensitivity)
		: sensitivity_x(sensitivity)
		, sensitivity_y(sensitivity)
		, sensitivity_z(sensitivity) {};
	FreeMove(float sensitivity_x, float sensitivity_y, float sensitivity_z)
		: sensitivity_x(sensitivity_x)
		, sensitivity_y(sensitivity_y)
		, sensitivity_z(sensitivity_z) {};

	void move(const Vector3f &direction, float amount) noexcept
	{
		get_parent_transform()->set_translation(
			get_parent_transform()->get_translation() +
			(direction * amount));
	}

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

		float move_multiplier = 10.0f * delta;

		if (input_handler.is_key_pressed(GLFW_KEY_W)) {
			this->move(this->get_forward(),
				   move_multiplier * sensitivity_x);
		}
		if (input_handler.is_key_pressed(GLFW_KEY_S)) {
			this->move(this->get_forward(),
				   -move_multiplier * sensitivity_x);
		}
		if (input_handler.is_key_pressed(GLFW_KEY_A)) {
			this->move(this->get_left(),
				   move_multiplier * sensitivity_y);
		}
		if (input_handler.is_key_pressed(GLFW_KEY_D)) {
			this->move(this->get_right(),
				   move_multiplier * sensitivity_y);
		}
		if (input_handler.is_key_pressed(GLFW_KEY_Q)) {
			this->move(this->get_up(),
				   move_multiplier * sensitivity_z);
		}
		if (input_handler.is_key_pressed(GLFW_KEY_E)) {
			this->move(this->get_up(),
				   -move_multiplier * sensitivity_z);
		}
	}

	void update(float) override {};
	void render(Shader &) override {};
};
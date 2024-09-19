#pragma once

#include <misc/glad.h>
#include <GLFW/glfw3.h>

#include <core/Input.h>

#include <components/GameComponent.h>

class FreeLook : public GameComponent {
	/***************************************************************************
	 * @brief Static member variable representing the Y-axis vector.
	 ***************************************************************************/
	const Vector3f y_axis{ 0, 1, 0 };

	float sensitivity_x, sensitivity_y;

    public:
	FreeLook(float sensitivity)
		: sensitivity_x(sensitivity)
		, sensitivity_y(sensitivity) {};
	FreeLook(float sensitivity_x, float sensitivity_y)
		: sensitivity_x(sensitivity_x)
		, sensitivity_y(sensitivity_y) {};
	/***************************************************************************
	 * @brief Moves the transform in the specified direction.
	 *
	 * Adjusts the transforms's position based on the given direction vector and amount.
	 *
	 * @param direction The direction to move the transform.
	 * @param amount The distance to move the transform.
	 ***************************************************************************/
	void move(const Vector3f &direction, float amount) noexcept
	{
		get_parent_transform()->set_translation(
			get_parent_transform()->get_translation() +
			(direction * amount));
	}

	/***************************************************************************
	 * @brief Gets the forward direction of the camera.
	 *
	 * @return The forward direction of the camera.
	 ***************************************************************************/
	Vector3f get_forward() const noexcept
	{
		return get_parent_transform()->get_rotation().get_forward();
	}

	/***************************************************************************
	 * @brief Gets the up direction of the camera.
	 *
	 * @return The up direction of the camera.
	 ***************************************************************************/
	Vector3f get_up() const noexcept
	{
		return get_parent_transform()->get_rotation().get_up();
	}

	/***************************************************************************
	 * @brief Gets the left direction of the camera.
	 *
	 * @return The left direction of the camera.
	 ***************************************************************************/
	Vector3f get_left() const noexcept
	{
		return get_parent_transform()->get_rotation().get_left();
	}

	/***************************************************************************
	 * @brief Gets the right direction of the camera.
	 *
	 * @return The right direction of the camera.
	 ***************************************************************************/
	Vector3f get_right() const noexcept
	{
		return get_parent_transform()->get_rotation().get_right();
	}

	/***************************************************************************
	 * @brief Processes input to adjust the transform.
	 ***************************************************************************/
	void input(float delta) override
	{
		Input &input_handler = Input::get_instance();

		float rotate_sensitivity = 100.0f * delta;

		if (input_handler.is_mouse_down(GLFW_MOUSE_BUTTON_2)) {
			const double *delta =
				input_handler.get_mouse_pos_delta();
			float dx = delta[0], dy = delta[1];

			if (dx != 0) {
				get_parent_transform()->rotate(
					y_axis,
					to_radians(-dx * rotate_sensitivity *
						   sensitivity_x));
			}
			if (dy != 0) {
				get_parent_transform()->rotate(
					get_right(),
					to_radians(dy * rotate_sensitivity *
						   sensitivity_y));
			}
		}
	}

	void update(float) override {};
	void render(Shader &) override {};
};
#include <core/Camera.h>

#include <misc/glad.h>
#include <GLFW/glfw3.h>

#include <core/Timer.h>
#include <core/Input.h>

#include <math/Vector3f.h>

const Vector3f Camera::y_axis{ 0, 1, 0 };

Camera &Camera::get_instance()
{
	static Camera instance;
	return instance;
}

Camera::Camera()
{
	position = Vector3f{ 0, 0, 0 };
	forward = Vector3f{ 0, 0, 1 };
	up = Vector3f{ 0, 1, 0 };
}

Camera::Camera(const Vector3f &position, const Vector3f &forward,
	       const Vector3f &up)
{
	this->position = position;
	this->forward = forward.normalize();
	this->up = up.normalize();
}

void Camera::set_position(const Vector3f &vec) noexcept
{
	position = vec;
}

void Camera::set_forward(const Vector3f &vec) noexcept
{
	forward = vec;
}

void Camera::set_up(const Vector3f &vec) noexcept
{
	up = vec;
}

Vector3f Camera::get_position() const noexcept
{
	return position;
}

Vector3f Camera::get_forward() const noexcept
{
	return forward;
}

Vector3f Camera::get_up() const noexcept
{
	return up;
}

Vector3f Camera::get_left() const noexcept
{
	return forward.cross(up).normalize();
}

Vector3f Camera::get_right() const noexcept
{
	return up.cross(forward).normalize();
}

void Camera::move_camera(const Vector3f &direction, float amount) noexcept
{
	position = position + (direction * amount);
}

void Camera::rotate_y(float angle) noexcept
{
	Vector3f horizontal_axis = y_axis.cross(forward).normalize();
	forward = forward.rotate(angle, horizontal_axis).normalize();
	up = forward.cross(horizontal_axis).normalize();
}

void Camera::rotate_x(float angle) noexcept
{
	Vector3f horizontal_axis = y_axis.cross(forward).normalize();
	forward = forward.rotate(angle, y_axis).normalize();
	up = forward.cross(horizontal_axis).normalize();
}

void Camera::input()
{
	Timer &timer = Timer::get_instance();
	Input &input_handler = Input::get_instance();

	float move_multiplier = 10.0f * timer.get_delta_time();
	float rotate_sensitivity = 40.0f * timer.get_delta_time();

	if (input_handler.is_key_pressed(GLFW_KEY_W)) {
		this->move_camera(this->get_forward(), move_multiplier);
	}
	if (input_handler.is_key_pressed(GLFW_KEY_S)) {
		this->move_camera(this->get_forward(), -move_multiplier);
	}
	if (input_handler.is_key_pressed(GLFW_KEY_A)) {
		this->move_camera(this->get_left(), move_multiplier);
	}
	if (input_handler.is_key_pressed(GLFW_KEY_D)) {
		this->move_camera(this->get_right(), move_multiplier);
	}
	if (input_handler.is_key_pressed(GLFW_KEY_Q)) {
		this->move_camera(this->get_up(), -move_multiplier);
	}
	if (input_handler.is_key_pressed(GLFW_KEY_E)) {
		this->move_camera(this->get_up(), move_multiplier);
	}

	if (input_handler.is_mouse_down(GLFW_MOUSE_BUTTON_2)) {
		const double *delta = input_handler.get_mouse_pos_delta();
		float dx = delta[0], dy = delta[1];

		if (dx != 0) {
			this->rotate_x(dx * rotate_sensitivity);
		}
		if (dy != 0) {
			this->rotate_y(dy * rotate_sensitivity);
		}
	}
}
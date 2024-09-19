#include <core/Camera.h>

#include <math/Vector3f.h>

const Vector3f Camera::y_axis{ 0, 1, 0 };

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
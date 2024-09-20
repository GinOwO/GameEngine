#include <components/Camera.h>

#include <core/Input.h>
#include <core/Timer.h>

#include <math/Vector3f.h>
#include <math/Matrix4f.h>

#include <exception>

bool Camera::perspective_set = false;

void Camera::set_projection(float fov, float aspect_ratio, float zNear,
			    float zFar)
{
	perspective_set = true;
	projection =
		Matrix4f::Perspective_Matrix(fov, aspect_ratio, zNear, zFar);
}

Matrix4f Camera::get_view_projection() const
{
	if (!perspective_set) {
		throw std::runtime_error(
			"ERROR: Perspective matrix not initialized");
	}
	Matrix4f camera_rotation = get_parent_transform()
					   ->get_transformed_rotation()
					   .conjugate()
					   .to_rotation_matrix();
	Matrix4f camera_translation = Matrix4f::Translation_Matrix(
		get_parent_transform()->get_transformed_position() * -1.0f);
	return projection * camera_rotation * camera_translation;
}

Vector3f Camera::get_position() const noexcept
{
	return get_parent_transform()->get_translation();
}

Vector3f Camera::get_forward() const noexcept
{
	return get_parent_transform()->get_rotation().get_forward();
}

Vector3f Camera::get_up() const noexcept
{
	return get_parent_transform()->get_rotation().get_up();
}

Vector3f Camera::get_left() const noexcept
{
	return get_parent_transform()->get_rotation().get_left();
}

Vector3f Camera::get_right() const noexcept
{
	return get_parent_transform()->get_rotation().get_right();
}
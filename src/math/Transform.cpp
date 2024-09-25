#include <math/Transform.h>

#include <math/Vector3f.h>
#include <math/Matrix4f.h>
#include <math/Quaternion.h>

#include <components/BaseCamera.h>

#include <iostream>

Transform::Transform()
	: parent_matrix{ Matrix4f::Identity_Matrix() }
{
	translation = Vector3f(0);
	rotation = Quaternion(0, 0, 0, 1);
	scale = Vector3f(1, 1, 1);

	prev_translation = Vector3f(-1e9);
}

Vector3f &Transform::get_translation() noexcept
{
	return translation;
}

Quaternion &Transform::get_rotation() noexcept
{
	return rotation;
}

Vector3f &Transform::get_scale() noexcept
{
	return scale;
}

Transform &Transform::set_translation(float x, float y, float z)
{
	this->set_translation({ x, y, z });
	return *this;
}

Transform &Transform::set_translation(Vector3f translation)
{
	this->translation = translation;
	return *this;
}

Transform &Transform::set_rotation(Quaternion rotation)
{
	this->rotation = rotation;
	return *this;
}

Transform &Transform::set_scale(float x, float y, float z)
{
	this->set_scale({ x, y, z });
	return *this;
}

Transform &Transform::set_scale(Vector3f scale)
{
	this->scale = scale;
	return *this;
}

Matrix4f Transform::get_transformation() noexcept
{
	if (parent != nullptr) {
		if (parent->has_changed()) {
			parent_matrix = parent->get_transformation();
		}
	}

	return parent_matrix * (Matrix4f::Translation_Matrix(translation) *
				(rotation.to_rotation_matrix() *
				 Matrix4f::Scale_Matrix(scale)));
}

Matrix4f Transform::get_projected_camera(BaseCamera *camera) noexcept
{
	return camera->get_view_projection() * get_transformation();
}

bool Transform::has_changed() noexcept
{
	if (parent != nullptr && (parent->has_changed() || first_update)) {
		first_update = false;
		return true;
	}

	return !(translation == prev_translation && scale == prev_scale &&
		 rotation == prev_rotation);
}

Vector3f Transform::get_transformed_position() noexcept
{
	return parent_matrix.transform(translation);
}

Quaternion Transform::get_transformed_rotation() noexcept
{
	Quaternion parent_rotation{ 0, 0, 0, 1 };
	if (parent != nullptr) {
		parent_rotation = parent->get_transformed_rotation();
	}

	return parent_rotation * rotation;
}

void Transform::update() noexcept
{
	prev_translation = translation;
	prev_rotation = rotation;
	prev_scale = scale;
}

Transform &Transform::rotate(const Vector3f &axis, float angle)
{
	rotation = (Quaternion::Rotation_Quaternion(axis, angle) * rotation)
			   .normalize();
	return *this;
}

void Transform::look_at(const Vector3f &point, const Vector3f &up) noexcept
{
	this->rotation = look_at_direction(point, up);
}

Quaternion Transform::look_at_direction(const Vector3f &point,
					const Vector3f &up) noexcept
{
	return Quaternion(Matrix4f::Rotation_Matrix(
		(point - this->translation).normalize(), up));
}
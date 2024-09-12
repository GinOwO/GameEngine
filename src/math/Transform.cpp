#include <math/Transform.h>

#include <math/Vector3f.h>
#include <math/Matrix4f.h>

#include <core/Camera.h>

#include <iostream>

Transform::Transform()
{
	translation = Vector3f();
	rotation = Vector3f();
	scale = Vector3f(1, 1, 1);
}

Vector3f Transform::get_translation()
{
	return translation;
}

Vector3f Transform::get_rotation()
{
	return rotation;
}

Vector3f Transform::get_scale()
{
	return scale;
}

void Transform::set_translation(float x, float y, float z)
{
	this->set_translation({ x, y, z });
}

void Transform::set_translation(Vector3f translation)
{
	this->translation = translation;
}

void Transform::set_rotation(float x, float y, float z)
{
	this->set_rotation({ x, y, z });
}

void Transform::set_rotation(Vector3f rotation)
{
	this->rotation = rotation;
}

void Transform::set_scale(float x, float y, float z)
{
	this->set_rotation({ x, y, z });
}

void Transform::set_scale(Vector3f scale)
{
	this->scale = scale;
}

Matrix4f Transform::get_transformation() const noexcept
{
	return Matrix4f::Translation_Matrix(translation) *
	       (Matrix4f::Rotation_Matrix(rotation) *
		Matrix4f::Scale_Matrix(scale));
}

Matrix4f Transform::get_projected_camera(Camera &camera) const noexcept
{
	return camera.get_view_projection() * get_transformation();
}
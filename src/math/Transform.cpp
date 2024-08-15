#include <math/Transform.h>

#include <math/Vector3f.h>
#include <math/Matrix4f.h>

float Transform::zNear = 0;
float Transform::zFar = 0;
float Transform::width = 0;
float Transform::height = 0;
float Transform::fov = 0;

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

void Transform::set_projection(float fov, float width, float height,
			       float zNear, float zFar)
{
	Transform::fov = fov;
	Transform::width = width;
	Transform::height = height;
	Transform::zNear = zNear;
	Transform::zFar = zFar;
}

Matrix4f Transform::get_transformation()
{
	return Matrix4f::Translation_Matrix(translation) *
	       (Matrix4f::Rotation_Matrix(rotation) *
		Matrix4f::Scale_Matrix(scale));
}

Matrix4f Transform::get_projected_transformation()
{
	Matrix4f projection_matrix =
		Matrix4f::Projection_Matrix(fov, width, height, zNear, zFar);
	Matrix4f transformation_matrix = this->get_transformation();
	Matrix4f resultant_matrix = projection_matrix * transformation_matrix;
	return resultant_matrix;
}
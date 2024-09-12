#include <math/Transform.h>

#include <math/Vector3f.h>
#include <math/Matrix4f.h>

#include <core/Camera.h>

#include <iostream>

/***************************************************************************
 * @brief Default constructor for Transform.
 *
 * Initializes the translation and rotation to (0, 0, 0) and scale to (1, 1, 1).
 ***************************************************************************/
Transform::Transform()
{
	translation = Vector3f();
	rotation = Vector3f();
	scale = Vector3f(1, 1, 1);
}

/***************************************************************************
 * @brief Gets the translation vector of the transform.
 *
 * @return The translation vector.
 ***************************************************************************/
Vector3f Transform::get_translation()
{
	return translation;
}

/***************************************************************************
 * @brief Gets the rotation vector of the transform.
 *
 * @return The rotation vector.
 ***************************************************************************/
Vector3f Transform::get_rotation()
{
	return rotation;
}

/***************************************************************************
 * @brief Gets the scale vector of the transform.
 *
 * @return The scale vector.
 ***************************************************************************/
Vector3f Transform::get_scale()
{
	return scale;
}

/***************************************************************************
 * @brief Sets the translation using individual float components.
 *
 * @param x The x component of the translation.
 * @param y The y component of the translation.
 * @param z The z component of the translation.
 ***************************************************************************/
void Transform::set_translation(float x, float y, float z)
{
	this->set_translation({ x, y, z });
}

/***************************************************************************
 * @brief Sets the translation using a Vector3f.
 *
 * @param translation The new translation vector.
 ***************************************************************************/
void Transform::set_translation(Vector3f translation)
{
	this->translation = translation;
}

/***************************************************************************
 * @brief Sets the rotation using individual float components.
 *
 * @param x The x component of the rotation.
 * @param y The y component of the rotation.
 * @param z The z component of the rotation.
 ***************************************************************************/
void Transform::set_rotation(float x, float y, float z)
{
	this->set_rotation({ x, y, z });
}

/***************************************************************************
 * @brief Sets the rotation using a Vector3f.
 *
 * @param rotation The new rotation vector.
 ***************************************************************************/
void Transform::set_rotation(Vector3f rotation)
{
	this->rotation = rotation;
}

/***************************************************************************
 * @brief Sets the scale using individual float components.
 *
 * @param x The x component of the scale.
 * @param y The y component of the scale.
 * @param z The z component of the scale.
 ***************************************************************************/
void Transform::set_scale(float x, float y, float z)
{
	this->set_scale({ x, y, z });
}

/***************************************************************************
 * @brief Sets the scale using a Vector3f.
 *
 * @param scale The new scale vector.
 ***************************************************************************/
void Transform::set_scale(Vector3f scale)
{
	this->scale = scale;
}

/***************************************************************************
 * @brief Computes the transformation matrix based on the translation, 
 *        rotation, and scale.
 *
 * @return The resulting transformation matrix.
 ***************************************************************************/
Matrix4f Transform::get_transformation() const noexcept
{
	return Matrix4f::Translation_Matrix(translation) *
	       (Matrix4f::Rotation_Matrix(rotation) *
		Matrix4f::Scale_Matrix(scale));
}

/***************************************************************************
 * @brief Computes the transformation matrix projected onto a camera's 
 *        view and projection matrix.
 *
 * @param camera The camera to project the transformation onto.
 * @return The resulting matrix from the camera's view-projection and 
 *         the transform.
 ***************************************************************************/
Matrix4f Transform::get_projected_camera(Camera &camera) const noexcept
{
	return camera.get_view_projection() * get_transformation();
}

#include <components/Camera.h>

#include <core/Input.h>
#include <core/Timer.h>

#include <math/Vector3f.h>
#include <math/Matrix4f.h>

#include <exception>

bool Camera::perspective_set = false;

/***************************************************************************
 * @brief Sets the projection matrix for the camera.
 *
 * Initializes the perspective projection matrix with the given field of view,
 * aspect ratio, and near and far clipping planes.
 *
 * @param fov Field of view in degrees.
 * @param aspect_ratio Aspect ratio of the viewport.
 * @param zNear Near clipping plane distance.
 * @param zFar Far clipping plane distance.
 ***************************************************************************/
void Camera::set_projection(float fov, float aspect_ratio, float zNear,
			    float zFar)
{
	perspective_set = true;
	projection =
		Matrix4f::Perspective_Matrix(fov, aspect_ratio, zNear, zFar);
}

/***************************************************************************
 * @brief Computes the view-projection matrix for the camera.
 *
 * Calculates the combined view and projection matrix. Throws an exception
 * if the perspective matrix has not been set.
 *
 * @return The view-projection matrix.
 * @throws std::runtime_error if the perspective matrix has not been set.
 ***************************************************************************/
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

/***************************************************************************
 * @brief Gets the position of the camera.
 *
 * @return The position of the camera.
 ***************************************************************************/
Vector3f Camera::get_position() const noexcept
{
	return get_parent_transform()->get_translation();
}

/***************************************************************************
 * @brief Gets the forward direction of the camera.
 *
 * @return The forward direction of the camera.
 ***************************************************************************/
Vector3f Camera::get_forward() const noexcept
{
	return get_parent_transform()->get_rotation().get_forward();
}

/***************************************************************************
 * @brief Gets the up direction of the camera.
 *
 * @return The up direction of the camera.
 ***************************************************************************/
Vector3f Camera::get_up() const noexcept
{
	return get_parent_transform()->get_rotation().get_up();
}

/***************************************************************************
 * @brief Gets the left direction of the camera.
 *
 * @return The left direction of the camera.
 ***************************************************************************/
Vector3f Camera::get_left() const noexcept
{
	return get_parent_transform()->get_rotation().get_left();
}

/***************************************************************************
 * @brief Gets the right direction of the camera.
 *
 * @return The right direction of the camera.
 ***************************************************************************/
Vector3f Camera::get_right() const noexcept
{
	return get_parent_transform()->get_rotation().get_right();
}
#include <components/Camera.h>

#include <misc/glad.h>
#include <GLFW/glfw3.h>

#include <core/Input.h>
#include <core/Timer.h>

#include <math/Vector3f.h>
#include <math/Matrix4f.h>

#include <exception>

const Vector3f Camera::y_axis{ 0, 1, 0 };
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
	Matrix4f camera_rotation =
		get_parent_transform()->get_rotation().to_rotation_matrix();
	Matrix4f camera_translation = Matrix4f::Translation_Matrix(
		get_parent_transform()->get_translation() * -1.0f);
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

/***************************************************************************
 * @brief Moves the camera in the specified direction.
 *
 * Adjusts the camera's position based on the given direction vector and amount.
 *
 * @param direction The direction to move the camera.
 * @param amount The distance to move the camera.
 ***************************************************************************/
void Camera::move_camera(const Vector3f &direction, float amount) noexcept
{
	get_parent_transform()->set_translation(
		get_parent_transform()->get_translation() +
		(direction * amount));
}

/***************************************************************************
 * @brief Handles camera input from the user.
 *
 * Processes keyboard and mouse input to move and rotate the camera.
 ***************************************************************************/
void Camera::input()
{
	Timer &timer = Timer::get_instance();
	Input &input_handler = Input::get_instance();

	float move_multiplier = 15.0f * timer.get_delta_time();
	float rotate_sensitivity = 35.0f * timer.get_delta_time();

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
		this->move_camera(this->get_up(), move_multiplier);
	}
	if (input_handler.is_key_pressed(GLFW_KEY_E)) {
		this->move_camera(this->get_up(), -move_multiplier);
	}

	if (input_handler.is_mouse_down(GLFW_MOUSE_BUTTON_2)) {
		const double *delta = input_handler.get_mouse_pos_delta();
		float dx = delta[0], dy = delta[1];

		if (abs(dx) > 5e-4) {
			get_parent_transform()->set_rotation(
				get_parent_transform()->get_rotation() *
				Quaternion::Rotation_Quaternion(
					y_axis,
					to_radians(-dx * rotate_sensitivity)));
		}
		if (abs(dy) > 5e-4) {
			get_parent_transform()->set_rotation(
				get_parent_transform()->get_rotation() *
				Quaternion::Rotation_Quaternion(
					get_parent_transform()
						->get_rotation()
						.get_right(),
					to_radians(-dy * rotate_sensitivity)));
		}
	}
}
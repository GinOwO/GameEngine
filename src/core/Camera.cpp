#include <core/Camera.h>

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
 * @brief Gets the singleton instance of the Camera class.
 *
 * This method ensures that only one instance of the Camera class exists
 * throughout the application.
 *
 * @return A reference to the singleton instance of the Camera class.
 ***************************************************************************/
Camera &Camera::get_instance()
{
	static Camera instance;
	return instance;
}

/***************************************************************************
 * @brief Constructs a Camera object with default settings.
 *
 * Initializes the camera's position, forward, and up vectors to default values.
 ***************************************************************************/
Camera::Camera()
{
	position = Vector3f{ 0, 0, 0 };
	forward = Vector3f{ 0, 0, 1 };
	up = Vector3f{ 0, 1, 0 };
}

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
	Matrix4f camera_rotation = Matrix4f::Camera_Matrix(forward, up);
	Matrix4f camera_translation =
		Matrix4f::Translation_Matrix(position * -1.0f);
	return projection * camera_rotation * camera_translation;
}

/***************************************************************************
 * @brief Sets the position of the camera.
 *
 * @param vec The new position of the camera.
 ***************************************************************************/
void Camera::set_position(const Vector3f &vec) noexcept
{
	position = vec;
}

/***************************************************************************
 * @brief Sets the forward direction of the camera.
 *
 * @param vec The new forward direction of the camera.
 ***************************************************************************/
void Camera::set_forward(const Vector3f &vec) noexcept
{
	forward = vec;
}

/***************************************************************************
 * @brief Sets the up direction of the camera.
 *
 * @param vec The new up direction of the camera.
 ***************************************************************************/
void Camera::set_up(const Vector3f &vec) noexcept
{
	up = vec;
}

/***************************************************************************
 * @brief Gets the position of the camera.
 *
 * @return The position of the camera.
 ***************************************************************************/
Vector3f Camera::get_position() const noexcept
{
	return position;
}

/***************************************************************************
 * @brief Gets the forward direction of the camera.
 *
 * @return The forward direction of the camera.
 ***************************************************************************/
Vector3f Camera::get_forward() const noexcept
{
	return forward;
}

/***************************************************************************
 * @brief Gets the up direction of the camera.
 *
 * @return The up direction of the camera.
 ***************************************************************************/
Vector3f Camera::get_up() const noexcept
{
	return up;
}

/***************************************************************************
 * @brief Gets the left direction of the camera.
 *
 * @return The left direction of the camera.
 ***************************************************************************/
Vector3f Camera::get_left() const noexcept
{
	return forward.cross(up).normalize();
}

/***************************************************************************
 * @brief Gets the right direction of the camera.
 *
 * @return The right direction of the camera.
 ***************************************************************************/
Vector3f Camera::get_right() const noexcept
{
	return up.cross(forward).normalize();
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
	position = position + (direction * amount);
}

/***************************************************************************
 * @brief Rotates the camera around the Y-axis.
 *
 * Rotates the camera's forward and up vectors based on the given angle.
 *
 * @param angle The angle to rotate the camera, in degrees.
 ***************************************************************************/
void Camera::rotate_y(float angle) noexcept
{
	Vector3f horizontal_axis = y_axis.cross(forward).normalize();
	forward = forward.rotate(angle, horizontal_axis).normalize();
	up = forward.cross(horizontal_axis).normalize();
}

/***************************************************************************
 * @brief Rotates the camera around the X-axis.
 *
 * Rotates the camera's forward and up vectors based on the given angle.
 *
 * @param angle The angle to rotate the camera, in degrees.
 ***************************************************************************/
void Camera::rotate_x(float angle) noexcept
{
	Vector3f horizontal_axis = y_axis.cross(forward).normalize();
	forward = forward.rotate(angle, y_axis).normalize();
	up = forward.cross(horizontal_axis).normalize();
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

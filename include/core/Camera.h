/***************************************************************************
 * @file Camera.h
 *
 * @brief Declares the Camera class, including its public and private methods
 *	and member variables.
 *
 * This file contains the declaration of the Camera class, which handles the
 * camera's position, orientation, and projection in the 3D space. The class
 * also includes methods for setting and getting the camera's attributes, as
 * well as moving and rotating the camera.
 *
 ***************************************************************************/

#pragma once

#include <math/Vector3f.h>
#include <math/Matrix4f.h>

/***************************************************************************
 * @class Camera
 *
 * @brief Singleton class managing the camera's position, orientation, and
 *	projection in 3D space.
 *
 * This class handles the camera's attributes and operations, including its
 * position, orientation vectors, and projection matrix. It provides methods
 * to set and get these attributes, move and rotate the camera, and calculate
 * the view-projection matrix.
 *
 ***************************************************************************/
class Camera {
    public:
	/***************************************************************************
	 * @brief Deleted copy constructor to prevent copying.
	 ***************************************************************************/
	Camera(const Camera &) = delete;

	/***************************************************************************
	 * @brief Deleted copy assignment operator to prevent copying.
	 ***************************************************************************/
	Camera &operator=(const Camera &) = delete;

	/***************************************************************************
	 * @brief Gets the singleton instance of the Camera class.
	 *
	 * @return Reference to the singleton Camera instance.
	 ***************************************************************************/
	static Camera &get_instance();

    private:
	/***************************************************************************
	 * @brief Static member variable representing the Y-axis vector.
	 ***************************************************************************/
	static const Vector3f y_axis;

	/***************************************************************************
	 * @brief Static flag indicating if the perspective projection is set.
	 ***************************************************************************/
	static bool perspective_set;

	/***************************************************************************
	 * @brief Camera position in 3D space.
	 ***************************************************************************/
	Vector3f position;

	/***************************************************************************
	 * @brief Forward direction vector of the camera.
	 ***************************************************************************/
	Vector3f forward;

	/***************************************************************************
	 * @brief Up direction vector of the camera.
	 ***************************************************************************/
	Vector3f up;

	/***************************************************************************
	 * @brief Projection matrix of the camera.
	 ***************************************************************************/
	Matrix4f projection;

	/***************************************************************************
	 * @brief Private constructor to prevent instantiation outside of the class.
	 ***************************************************************************/
	Camera();

    public:
	/***************************************************************************
	 * @brief Processes input to adjust the camera.
	 ***************************************************************************/
	void input();

	/***************************************************************************
	 * @brief Sets the camera's position.
	 *
	 * @param vec New position of the camera.
	 ***************************************************************************/
	void set_position(const Vector3f &vec) noexcept;

	/***************************************************************************
	 * @brief Sets the camera's forward direction.
	 *
	 * @param vec New forward direction of the camera.
	 ***************************************************************************/
	void set_forward(const Vector3f &vec) noexcept;

	/***************************************************************************
	 * @brief Sets the camera's up direction.
	 *
	 * @param vec New up direction of the camera.
	 ***************************************************************************/
	void set_up(const Vector3f &vec) noexcept;

	/***************************************************************************
	 * @brief Gets the camera's current position.
	 *
	 * @return The current position of the camera.
	 ***************************************************************************/
	Vector3f get_position() const noexcept;

	/***************************************************************************
	 * @brief Gets the camera's forward direction.
	 *
	 * @return The current forward direction of the camera.
	 ***************************************************************************/
	Vector3f get_forward() const noexcept;

	/***************************************************************************
	 * @brief Gets the camera's up direction.
	 *
	 * @return The current up direction of the camera.
	 ***************************************************************************/
	Vector3f get_up() const noexcept;

	/***************************************************************************
	 * @brief Gets the camera's left direction.
	 *
	 * @return The current left direction of the camera.
	 ***************************************************************************/
	Vector3f get_left() const noexcept;

	/***************************************************************************
	 * @brief Gets the camera's right direction.
	 *
	 * @return The current right direction of the camera.
	 ***************************************************************************/
	Vector3f get_right() const noexcept;

	/***************************************************************************
	 * @brief Moves the camera in a specified direction.
	 *
	 * @param direction Direction to move the camera.
	 * @param amount Distance to move the camera.
	 ***************************************************************************/
	void move_camera(const Vector3f &direction, float amount) noexcept;

	/***************************************************************************
	 * @brief Rotates the camera around the X-axis.
	 *
	 * @param angle Angle of rotation in radians.
	 ***************************************************************************/
	void rotate_x(float angle) noexcept;

	/***************************************************************************
	 * @brief Rotates the camera around the Y-axis.
	 *
	 * @param angle Angle of rotation in radians.
	 ***************************************************************************/
	void rotate_y(float angle) noexcept;

	/***************************************************************************
	 * @brief Sets the camera's projection parameters.
	 *
	 * @param fov Field of view angle in degrees.
	 * @param aspect_ratio Aspect ratio of the view.
	 * @param zNear Distance to the near clipping plane.
	 * @param zFar Distance to the far clipping plane.
	 ***************************************************************************/
	void set_projection(float fov, float aspect_ratio, float zNear,
			    float zFar);

	/***************************************************************************
	 * @brief Calculates the view-projection matrix for the camera.
	 *
	 * @return The view-projection matrix of the camera.
	 ***************************************************************************/
	Matrix4f get_view_projection() const;
};

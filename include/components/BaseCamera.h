/***************************************************************************
 * @file BaseCamera.h
 *
 * @brief Declares the BaseCamera class, including its public and private methods
 *	and member variables.
 *
 * This file contains the declaration of the BaseCamera class, which handles the
 * camera's position, orientation, and projection in the 3D space. The class
 * also includes methods for setting and getting the camera's attributes, as
 * well as moving and rotating the camera.
 *
 ***************************************************************************/

#pragma once

#include <math/Vector3f.h>
#include <math/Matrix4f.h>

/***************************************************************************
 * @class BaseCamera
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
class BaseCamera {
    protected:
	/***************************************************************************
	 * @brief Projection matrix of the camera.
	 ***************************************************************************/
	Matrix4f projection;

    public:
	/***************************************************************************
	 * @brief Processes input to adjust the camera.
	 ***************************************************************************/
	virtual void input() = 0;

	/***************************************************************************
	 * @brief Gets the camera's current position.
	 *
	 * @return The current position of the camera.
	 ***************************************************************************/
	virtual Vector3f get_position() const noexcept = 0;

	/***************************************************************************
	 * @brief Gets the camera's forward direction.
	 *
	 * @return The current forward direction of the camera.
	 ***************************************************************************/
	virtual Vector3f get_forward() const noexcept = 0;

	/***************************************************************************
	 * @brief Gets the camera's up direction.
	 *
	 * @return The current up direction of the camera.
	 ***************************************************************************/
	virtual Vector3f get_up() const noexcept = 0;

	/***************************************************************************
	 * @brief Gets the camera's left direction.
	 *
	 * @return The current left direction of the camera.
	 ***************************************************************************/
	virtual Vector3f get_left() const noexcept = 0;

	/***************************************************************************
	 * @brief Gets the camera's right direction.
	 *
	 * @return The current right direction of the camera.
	 ***************************************************************************/
	virtual Vector3f get_right() const noexcept = 0;

	/***************************************************************************
	 * @brief Moves the camera in a specified direction.
	 *
	 * @param direction Direction to move the camera.
	 * @param amount Distance to move the camera.
	 ***************************************************************************/
	virtual void move_camera(const Vector3f &direction,
				 float amount) noexcept = 0;

	/***************************************************************************
	 * @brief Sets the camera's projection parameters.
	 *
	 * @param fov Field of view angle in degrees.
	 * @param aspect_ratio Aspect ratio of the view.
	 * @param zNear Distance to the near clipping plane.
	 * @param zFar Distance to the far clipping plane.
	 ***************************************************************************/
	virtual void set_projection(float fov, float aspect_ratio, float zNear,
				    float zFar) = 0;

	/***************************************************************************
	 * @brief Calculates the view-projection matrix for the camera.
	 *
	 * @return The view-projection matrix of the camera.
	 ***************************************************************************/
	virtual Matrix4f get_view_projection() const = 0;
};

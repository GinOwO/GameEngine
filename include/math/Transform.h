/***************************************************************************
 * @file Transform.h
 *
 * @brief Declares the Transform class for handling transformations in 3D space.
 *
 * This file contains the declaration of the Transform class, which is used for
 * managing and applying transformations such as translation, rotation, and
 * scaling to objects in 3D space. It provides methods to set and get these
 * transformations as well as compute transformation matrices.
 *
 ***************************************************************************/

#pragma once

#include <math/Vector3f.h>
#include <math/Matrix4f.h>
#include <math/Quaternion.h>

#include <components/BaseCamera.h>

/***************************************************************************
 * @class Transform
 *
 * @brief Manages transformations including translation, rotation, and scaling.
 *
 * The Transform class encapsulates translation, rotation, and scaling vectors
 * for 3D transformations. It provides methods to set and retrieve these
 * transformations and to compute transformation matrices for rendering.
 *
 ***************************************************************************/
class Transform {
    private:
	Vector3f translation, prev_translation; /**< The translation vector. */
	Quaternion rotation, prev_rotation; /**< The rotation Quaternion. */
	Vector3f scale, prev_scale; /**< The scale vector. */
	Matrix4f parent_matrix;

    public:
	Transform *parent = nullptr; /**< The parent transform hierarchy. */

	/***************************************************************************
	 * @brief Default constructor for the Transform class.
	 *
	 * Initializes the transform with zero translation, rotation, and scale.
	 ***************************************************************************/
	Transform();

	/***************************************************************************
	 * @brief Gets the translation vector of the transform.
	 *
	 * @return The translation vector.
	 ***************************************************************************/
	Vector3f get_translation() const noexcept;

	/***************************************************************************
	 * @brief Gets the rotation vector of the transform.
	 *
	 * @return The rotation vector.
	 ***************************************************************************/
	Quaternion get_rotation() const noexcept;

	/***************************************************************************
	 * @brief Gets the scale vector of the transform.
	 *
	 * @return The scale vector.
	 ***************************************************************************/
	Vector3f get_scale() const noexcept;

	/***************************************************************************
	 * @brief Sets the translation vector using individual float values.
	 *
	 * @param x The x component of the translation.
	 * @param y The y component of the translation.
	 * @param z The z component of the translation.
	 ***************************************************************************/
	void set_translation(float x, float y, float z);

	/***************************************************************************
	 * @brief Sets the translation vector using a Vector3f object.
	 *
	 * @param translation The new translation vector.
	 ***************************************************************************/
	void set_translation(Vector3f translation);

	/***************************************************************************
	 * @brief Sets the rotation vector using a Vector3f object.
	 *
	 * @param rotation The new rotation vector (Euler angles).
	 ***************************************************************************/
	void set_rotation(Quaternion rotation);

	/***************************************************************************
	 * @brief Sets the scale vector using a Vector3f object.
	 *
	 * @param scale The new scale vector.
	 ***************************************************************************/
	void set_scale(Vector3f scale);

	/***************************************************************************
	 * @brief Sets the scale vector using individual float values.
	 *
	 * @param x The x component of the scale.
	 * @param y The y component of the scale.
	 * @param z The z component of the scale.
	 ***************************************************************************/
	void set_scale(float x, float y, float z);

	/***************************************************************************
	 * @brief Computes the transformation matrix based on translation, rotation, and scale.
	 *
	 * @return The transformation matrix.
	 ***************************************************************************/
	Matrix4f get_transformation() noexcept;

	/***************************************************************************
	 * @brief Computes the transformation matrix for projecting the camera view.
	 *
	 * @param camera The camera object for which the projection is computed.
	 * @return The projection matrix relative to the camera.
	 ***************************************************************************/
	Matrix4f get_projected_camera(BaseCamera *camera) noexcept;

	bool has_changed() noexcept;
};

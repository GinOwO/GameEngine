/***************************************************************************
 * @file Quaternion.h
 *
 * @brief Declares the Quaternion class for representing and manipulating
 *	quaternions.
 *
 * This file contains the declaration of the Quaternion class, which represents
 * a quaternion for 3D rotations. It provides methods for quaternion operations
 * such as normalization, conjugation, and arithmetic operations with other
 * quaternions and vectors.
 *
 ***************************************************************************/

#pragma once

#include <math/Vector3f.h>
#include <math/Matrix4f.h>

#include <array>

/***************************************************************************
 * @class Quaternion
 *
 * @brief Represents a quaternion for 3D rotations and provides various
 *	quaternion operations.
 *
 * The Quaternion class encapsulates a quaternion with x, y, z, and w components.
 * It supports operations such as addition, subtraction, multiplication,
 * and division with other quaternions and vectors. It also provides methods
 * for quaternion normalization and conjugation.
 *
 ***************************************************************************/
class Quaternion {
    private:
	float x; /**< The x component of the quaternion. */
	float y; /**< The y component of the quaternion. */
	float z; /**< The z component of the quaternion. */
	float w; /**< The w component of the quaternion. */

    public:
	/***************************************************************************
	 * @brief Returns the forward direction based on the quaternion.
	 *
	 * @return A Vector3f representing the forward direction.
	 ***************************************************************************/
	Vector3f get_forward() const;

	/***************************************************************************
	 * @brief Returns the back direction based on the quaternion.
	 *
	 * @return A Vector3f representing the back direction.
	 ***************************************************************************/
	Vector3f get_backward() const;

	/***************************************************************************
	 * @brief Returns the up direction based on the quaternion.
	 *
	 * @return A Vector3f representing the up direction.
	 ***************************************************************************/
	Vector3f get_up() const;

	/***************************************************************************
	 * @brief Returns the down direction based on the quaternion.
	 *
	 * @return A Vector3f representing the down direction.
	 ***************************************************************************/
	Vector3f get_down() const;

	/***************************************************************************
	 * @brief Returns the right direction based on the quaternion.
	 *
	 * @return A Vector3f representing the right direction.
	 ***************************************************************************/
	Vector3f get_right() const;

	/***************************************************************************
	 * @brief Returns the left direction based on the quaternion.
	 *
	 * @return A Vector3f representing the left direction.
	 ***************************************************************************/
	Vector3f get_left() const;
	/***************************************************************************
	 * @brief Default constructor for the Quaternion class.
	 *
	 * Initializes the quaternion to (0, 0, 0, 1).
	 ***************************************************************************/
	Quaternion();

	/***************************************************************************
	 * @brief Constructs a Quaternion with given components.
	 *
	 * @param a The x component.
	 * @param b The y component.
	 * @param c The z component.
	 * @param d The w component.
	 ***************************************************************************/
	Quaternion(float a, float b, float c, float d);

	/***************************************************************************
	 * @brief Sets the x component of the quaternion.
	 *
	 * @param a The x component value.
	 ***************************************************************************/
	void setX(float a) noexcept;

	/***************************************************************************
	 * @brief Sets the y component of the quaternion.
	 *
	 * @param b The y component value.
	 ***************************************************************************/
	void setY(float b) noexcept;

	/***************************************************************************
	 * @brief Sets the z component of the quaternion.
	 *
	 * @param c The z component value.
	 ***************************************************************************/
	void setZ(float c) noexcept;

	/***************************************************************************
	 * @brief Sets the w component of the quaternion.
	 *
	 * @param d The w component value.
	 ***************************************************************************/
	void setW(float d) noexcept;

	/***************************************************************************
	 * @brief Gets the x component of the quaternion.
	 *
	 * @return The x component.
	 ***************************************************************************/
	float getX() const noexcept;

	/***************************************************************************
	 * @brief Gets the y component of the quaternion.
	 *
	 * @return The y component.
	 ***************************************************************************/
	float getY() const noexcept;

	/***************************************************************************
	 * @brief Gets the z component of the quaternion.
	 *
	 * @return The z component.
	 ***************************************************************************/
	float getZ() const noexcept;

	/***************************************************************************
	 * @brief Gets the w component of the quaternion.
	 *
	 * @return The w component.
	 ***************************************************************************/
	float getW() const noexcept;

	/***************************************************************************
	 * @brief Gets all the components of the quaternion as an array<float, 4>.
	 *
	 * @return Array<float, 4> as (x, y, z, w).
	 ***************************************************************************/
	std::array<float, 4> get() const noexcept;

	/***************************************************************************
	 * @brief Calculates the length (magnitude) of the quaternion.
	 *
	 * @return The length of the quaternion.
	 ***************************************************************************/
	float length() const noexcept;

	/***************************************************************************
	 * @brief Normalizes the quaternion.
	 *
	 * @return The normalized quaternion.
	 ***************************************************************************/
	Quaternion normalize() const noexcept;

	/***************************************************************************
	 * @brief Computes the conjugate of the quaternion.
	 *
	 * @return The conjugate quaternion.
	 ***************************************************************************/
	Quaternion conjugate() const noexcept;

	/***************************************************************************
	 * @brief Adds another quaternion to this quaternion.
	 *
	 * @param v The quaternion to add.
	 * @return The result of the addition.
	 ***************************************************************************/
	Quaternion operator+(const Quaternion &v) const noexcept;

	/***************************************************************************
	 * @brief Subtracts another quaternion from this quaternion.
	 *
	 * @param v The quaternion to subtract.
	 * @return The result of the subtraction.
	 ***************************************************************************/
	Quaternion operator-(const Quaternion &v) const noexcept;

	/***************************************************************************
	 * @brief Multiplies this quaternion by another quaternion.
	 *
	 * @param v The quaternion to multiply with.
	 * @return The result of the multiplication.
	 ***************************************************************************/
	Quaternion operator*(const Quaternion &v) const noexcept;

	/***************************************************************************
	 * @brief Multiplies this quaternion by a vector.
	 *
	 * @param v The vector to multiply with.
	 * @return The result of the multiplication.
	 ***************************************************************************/
	Quaternion operator*(const Vector3f &v) const noexcept;

	/***************************************************************************
	 * @brief Divides this quaternion by another quaternion.
	 *
	 * @param v The quaternion to divide by.
	 * @return The result of the division.
	 ***************************************************************************/
	Quaternion operator/(const Quaternion &v) const noexcept;

	/***************************************************************************
	 * @brief Adds a scalar to this quaternion.
	 *
	 * @param r The scalar to add.
	 * @return The result of the addition.
	 ***************************************************************************/
	Quaternion operator+(const float r) const noexcept;

	/***************************************************************************
	 * @brief Subtracts a scalar from this quaternion.
	 *
	 * @param r The scalar to subtract.
	 * @return The result of the subtraction.
	 ***************************************************************************/
	Quaternion operator-(const float r) const noexcept;

	/***************************************************************************
	 * @brief Multiplies this quaternion by a scalar.
	 *
	 * @param r The scalar to multiply by.
	 * @return The result of the multiplication.
	 ***************************************************************************/
	Quaternion operator*(const float r) const noexcept;

	/***************************************************************************
	 * @brief Divides this quaternion by a scalar.
	 *
	 * @param r The scalar to divide by.
	 * @return The result of the division.
	 ***************************************************************************/
	Quaternion operator/(const float r) const noexcept;

	/***************************************************************************
	 * @brief Adds another quaternion to this quaternion (in-place).
	 *
	 * @param v The quaternion to add.
	 * @return A reference to this quaternion after addition.
	 ***************************************************************************/
	Quaternion &operator+=(const Quaternion &v);

	/***************************************************************************
	 * @brief Subtracts another quaternion from this quaternion (in-place).
	 *
	 * @param v The quaternion to subtract.
	 * @return A reference to this quaternion after subtraction.
	 ***************************************************************************/
	Quaternion &operator-=(const Quaternion &v);

	/***************************************************************************
	 * @brief Multiplies this quaternion by another quaternion (in-place).
	 *
	 * @param v The quaternion to multiply with.
	 * @return A reference to this quaternion after multiplication.
	 ***************************************************************************/
	Quaternion &operator*=(const Quaternion &v);

	/***************************************************************************
	 * @brief Multiplies this quaternion by a vector (in-place).
	 *
	 * @param v The vector to multiply with.
	 * @return A reference to this quaternion after multiplication.
	 ***************************************************************************/
	Quaternion &operator*=(const Vector3f &v);

	/***************************************************************************
	 * @brief Divides this quaternion by another quaternion (in-place).
	 *
	 * @param v The quaternion to divide by.
	 * @return A reference to this quaternion after division.
	 ***************************************************************************/
	Quaternion &operator/=(const Quaternion &v);

	/***************************************************************************
	 * @brief Adds a scalar to this quaternion (in-place).
	 *
	 * @param r The scalar to add.
	 * @return A reference to this quaternion after addition.
	 ***************************************************************************/
	Quaternion &operator+=(const float r);

	/***************************************************************************
	 * @brief Subtracts a scalar from this quaternion (in-place).
	 *
	 * @param r The scalar to subtract.
	 * @return A reference to this quaternion after subtraction.
	 ***************************************************************************/
	Quaternion &operator-=(const float r);

	/***************************************************************************
	 * @brief Multiplies this quaternion by a scalar (in-place).
	 *
	 * @param r The scalar to multiply by.
	 * @return A reference to this quaternion after multiplication.
	 ***************************************************************************/
	Quaternion &operator*=(const float r);

	/***************************************************************************
	 * @brief Divides this quaternion by a scalar (in-place).
	 *
	 * @param r The scalar to divide by.
	 * @return A reference to this quaternion after division.
	 ***************************************************************************/
	Quaternion &operator/=(const float r);

	/***************************************************************************
	 * @brief Checks if this quaternion is equal to another quaternion.
	 *
	 * @param q The quaternion to compare with.
	 * @return True if the quaternions are equal, false otherwise.
	 ***************************************************************************/
	bool operator==(const Quaternion &q) const noexcept;

	//TODO: Comment
	Matrix4f to_rotation_matrix() const noexcept;
	static Quaternion Rotation_Quaternion(const Vector3f &axis,
					      float angle) noexcept;
};

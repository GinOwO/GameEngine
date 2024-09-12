/***************************************************************************
 * @file Vector3f.h
 *
 * @brief Declares the Vector3f class for 3D vector operations.
 *
 * This file contains the declaration of the Vector3f class, which represents
 * a 3D vector and provides various operations such as addition, subtraction,
 * dot product, cross product, and normalization.
 *
 ***************************************************************************/

#pragma once

#include <array>

/***************************************************************************
 * @class Vector3f
 *
 * @brief Represents a 3D vector with basic vector operations.
 *
 * The Vector3f class provides functionality for 3D vector operations including
 * setting and getting vector components, calculating length, dot product,
 * cross product, and normalizing the vector. It also supports arithmetic
 * operations and rotation around a given axis.
 *
 ***************************************************************************/
class Vector3f {
    private:
	float x; /**< The x component of the vector. */
	float y; /**< The y component of the vector. */
	float z; /**< The z component of the vector. */

    public:
	/***************************************************************************
	 * @brief Default constructor for the Vector3f class.
	 *
	 * Initializes the vector with zero components.
	 ***************************************************************************/
	Vector3f();

	/***************************************************************************
	 * @brief Parameterized constructor for the Vector3f class with one value.
	 *
	 * @param a The x, y, and z components of the vector.
	 ***************************************************************************/
	Vector3f(float a);

	/***************************************************************************
	 * @brief Parameterized constructor for the Vector3f class with three values.
	 *
	 * @param a The x component of the vector.
	 * @param b The y component of the vector.
	 * @param c The z component of the vector.
	 ***************************************************************************/
	Vector3f(float a, float b, float c);

	/***************************************************************************
	 * @brief Sets the x component of the vector.
	 *
	 * @param a The new x component value.
	 ***************************************************************************/
	void setX(float a) noexcept;

	/***************************************************************************
	 * @brief Sets the y component of the vector.
	 *
	 * @param b The new y component value.
	 ***************************************************************************/
	void setY(float b) noexcept;

	/***************************************************************************
	 * @brief Sets the z component of the vector.
	 *
	 * @param c The new z component value.
	 ***************************************************************************/
	void setZ(float c) noexcept;

	/***************************************************************************
	 * @brief Gets the x component of the vector.
	 *
	 * @return The x component value.
	 ***************************************************************************/
	float getX() const noexcept;

	/***************************************************************************
	 * @brief Gets the y component of the vector.
	 *
	 * @return The y component value.
	 ***************************************************************************/
	float getY() const noexcept;

	/***************************************************************************
	 * @brief Gets the z component of the vector.
	 *
	 * @return The z component value.
	 ***************************************************************************/
	float getZ() const noexcept;

	/***************************************************************************
	 * @brief Gets the vector components as an array.
	 *
	 * @return An array containing the x, y, and z components.
	 ***************************************************************************/
	std::array<float, 3> get() const noexcept;

	/***************************************************************************
	 * @brief Calculates the length (magnitude) of the vector.
	 *
	 * @return The length of the vector.
	 ***************************************************************************/
	float length() const noexcept;

	/***************************************************************************
	 * @brief Computes the dot product of this vector with another vector.
	 *
	 * @param v The other vector.
	 * @return The dot product result.
	 ***************************************************************************/
	float dot(const Vector3f &v) noexcept;

	/***************************************************************************
	 * @brief Normalizes the vector to have unit length.
	 *
	 * @return The normalized vector.
	 ***************************************************************************/
	Vector3f normalize() const noexcept;

	/***************************************************************************
	 * @brief Adds another vector to this vector.
	 *
	 * @param v The vector to add.
	 * @return The resulting vector after addition.
	 ***************************************************************************/
	Vector3f operator+(const Vector3f &v) const noexcept;

	/***************************************************************************
	 * @brief Subtracts another vector from this vector.
	 *
	 * @param v The vector to subtract.
	 * @return The resulting vector after subtraction.
	 ***************************************************************************/
	Vector3f operator-(const Vector3f &v) const noexcept;

	/***************************************************************************
	 * @brief Multiplies this vector by another vector element-wise.
	 *
	 * @param v The vector to multiply.
	 * @return The resulting vector after multiplication.
	 ***************************************************************************/
	Vector3f operator*(const Vector3f &v) const noexcept;

	/***************************************************************************
	 * @brief Divides this vector by another vector element-wise.
	 *
	 * @param v The vector to divide.
	 * @return The resulting vector after division.
	 ***************************************************************************/
	Vector3f operator/(const Vector3f &v) const noexcept;

	/***************************************************************************
	 * @brief Adds a scalar value to each component of this vector.
	 *
	 * @param r The scalar value to add.
	 * @return The resulting vector after addition.
	 ***************************************************************************/
	Vector3f operator+(const float r) const noexcept;

	/***************************************************************************
	 * @brief Subtracts a scalar value from each component of this vector.
	 *
	 * @param r The scalar value to subtract.
	 * @return The resulting vector after subtraction.
	 ***************************************************************************/
	Vector3f operator-(const float r) const noexcept;

	/***************************************************************************
	 * @brief Multiplies each component of this vector by a scalar value.
	 *
	 * @param r The scalar value to multiply.
	 * @return The resulting vector after multiplication.
	 ***************************************************************************/
	Vector3f operator*(const float r) const noexcept;

	/***************************************************************************
	 * @brief Divides each component of this vector by a scalar value.
	 *
	 * @param r The scalar value to divide.
	 * @return The resulting vector after division.
	 ***************************************************************************/
	Vector3f operator/(const float r) const noexcept;

	/***************************************************************************
	 * @brief Adds another vector to this vector (compound assignment).
	 *
	 * @param v The vector to add.
	 * @return A reference to this vector after addition.
	 ***************************************************************************/
	Vector3f &operator+=(const Vector3f &v);

	/***************************************************************************
	 * @brief Subtracts another vector from this vector (compound assignment).
	 *
	 * @param v The vector to subtract.
	 * @return A reference to this vector after subtraction.
	 ***************************************************************************/
	Vector3f &operator-=(const Vector3f &v);

	/***************************************************************************
	 * @brief Multiplies this vector by another vector element-wise (compound assignment).
	 *
	 * @param v The vector to multiply.
	 * @return A reference to this vector after multiplication.
	 ***************************************************************************/
	Vector3f &operator*=(const Vector3f &v);

	/***************************************************************************
	 * @brief Divides this vector by another vector element-wise (compound assignment).
	 *
	 * @param v The vector to divide.
	 * @return A reference to this vector after division.
	 ***************************************************************************/
	Vector3f &operator/=(const Vector3f &v);

	/***************************************************************************
	 * @brief Adds a scalar value to each component of this vector (compound assignment).
	 *
	 * @param r The scalar value to add.
	 * @return A reference to this vector after addition.
	 ***************************************************************************/
	Vector3f &operator+=(const float r);

	/***************************************************************************
	 * @brief Subtracts a scalar value from each component of this vector (compound assignment).
	 *
	 * @param r The scalar value to subtract.
	 * @return A reference to this vector after subtraction.
	 ***************************************************************************/
	Vector3f &operator-=(const float r);

	/***************************************************************************
	 * @brief Multiplies each component of this vector by a scalar value (compound assignment).
	 *
	 * @param r The scalar value to multiply.
	 * @return A reference to this vector after multiplication.
	 ***************************************************************************/
	Vector3f &operator*=(const float r);

	/***************************************************************************
	 * @brief Divides each component of this vector by a scalar value (compound assignment).
	 *
	 * @param r The scalar value to divide.
	 * @return A reference to this vector after division.
	 ***************************************************************************/
	Vector3f &operator/=(const float r);

	/***************************************************************************
	 * @brief Compares this vector to another vector for equality.
	 *
	 * @param v The vector to compare with.
	 * @return True if the vectors are equal, false otherwise.
	 ***************************************************************************/
	bool operator==(const Vector3f &v) const noexcept;

	/***************************************************************************
	 * @brief Computes the cross product of this vector with another vector.
	 *
	 * @param v The other vector.
	 * @return The cross product result.
	 ***************************************************************************/
	Vector3f cross(const Vector3f &v) const noexcept;

	/***************************************************************************
	 * @brief Rotates the vector around a given axis by a specified angle.
	 *
	 * @param angle The angle in degrees to rotate the vector.
	 * @param axis The axis to rotate around.
	 * @return The rotated vector.
	 ***************************************************************************/
	Vector3f rotate(const float angle, const Vector3f &axis) const noexcept;
};

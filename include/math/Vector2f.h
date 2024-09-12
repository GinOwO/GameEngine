/***************************************************************************
 * @file Vector2f.h
 *
 * @brief Declares the Vector2f class for 2D vector operations.
 *
 * This file contains the declaration of the Vector2f class, which represents
 * a 2D vector and provides various operations such as addition, subtraction,
 * dot product, and normalization.
 *
 ***************************************************************************/

#pragma once

#include <array>

/***************************************************************************
 * @class Vector2f
 *
 * @brief Represents a 2D vector with basic vector operations.
 *
 * The Vector2f class provides functionality for 2D vector operations including
 * setting and getting vector components, calculating length, dot product,
 * and normalizing the vector. It also supports arithmetic operations and
 * rotation of the vector.
 *
 ***************************************************************************/
class Vector2f {
    private:
	float x; /**< The x component of the vector. */
	float y; /**< The y component of the vector. */

    public:
	/***************************************************************************
	 * @brief Default constructor for the Vector2f class.
	 *
	 * Initializes the vector with zero components.
	 ***************************************************************************/
	Vector2f();

	/***************************************************************************
	 * @brief Parameterized constructor for the Vector2f class.
	 *
	 * @param a The x component of the vector.
	 * @param b The y component of the vector.
	 ***************************************************************************/
	Vector2f(float a, float b);

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
	 * @brief Gets the vector components as an array.
	 *
	 * @return An array containing the x and y components.
	 ***************************************************************************/
	std::array<float, 2> get() const noexcept;

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
	float dot(const Vector2f &v) const noexcept;

	/***************************************************************************
	 * @brief Normalizes the vector to have unit length.
	 *
	 * @return The normalized vector.
	 ***************************************************************************/
	Vector2f normalize() const noexcept;

	/***************************************************************************
	 * @brief Adds another vector to this vector.
	 *
	 * @param v The vector to add.
	 * @return The resulting vector after addition.
	 ***************************************************************************/
	Vector2f operator+(const Vector2f &v) const noexcept;

	/***************************************************************************
	 * @brief Subtracts another vector from this vector.
	 *
	 * @param v The vector to subtract.
	 * @return The resulting vector after subtraction.
	 ***************************************************************************/
	Vector2f operator-(const Vector2f &v) const noexcept;

	/***************************************************************************
	 * @brief Multiplies this vector by another vector element-wise.
	 *
	 * @param v The vector to multiply.
	 * @return The resulting vector after multiplication.
	 ***************************************************************************/
	Vector2f operator*(const Vector2f &v) const noexcept;

	/***************************************************************************
	 * @brief Divides this vector by another vector element-wise.
	 *
	 * @param v The vector to divide.
	 * @return The resulting vector after division.
	 ***************************************************************************/
	Vector2f operator/(const Vector2f &v) const noexcept;

	/***************************************************************************
	 * @brief Adds a scalar value to each component of this vector.
	 *
	 * @param r The scalar value to add.
	 * @return The resulting vector after addition.
	 ***************************************************************************/
	Vector2f operator+(const float r) const noexcept;

	/***************************************************************************
	 * @brief Subtracts a scalar value from each component of this vector.
	 *
	 * @param r The scalar value to subtract.
	 * @return The resulting vector after subtraction.
	 ***************************************************************************/
	Vector2f operator-(const float r) const noexcept;

	/***************************************************************************
	 * @brief Multiplies each component of this vector by a scalar value.
	 *
	 * @param r The scalar value to multiply.
	 * @return The resulting vector after multiplication.
	 ***************************************************************************/
	Vector2f operator*(const float r) const noexcept;

	/***************************************************************************
	 * @brief Divides each component of this vector by a scalar value.
	 *
	 * @param r The scalar value to divide.
	 * @return The resulting vector after division.
	 ***************************************************************************/
	Vector2f operator/(const float r) const noexcept;

	/***************************************************************************
	 * @brief Adds another vector to this vector (compound assignment).
	 *
	 * @param v The vector to add.
	 * @return A reference to this vector after addition.
	 ***************************************************************************/
	Vector2f &operator+=(const Vector2f &v);

	/***************************************************************************
	 * @brief Subtracts another vector from this vector (compound assignment).
	 *
	 * @param v The vector to subtract.
	 * @return A reference to this vector after subtraction.
	 ***************************************************************************/
	Vector2f &operator-=(const Vector2f &v);

	/***************************************************************************
	 * @brief Multiplies this vector by another vector element-wise (compound assignment).
	 *
	 * @param v The vector to multiply.
	 * @return A reference to this vector after multiplication.
	 ***************************************************************************/
	Vector2f &operator*=(const Vector2f &v);

	/***************************************************************************
	 * @brief Divides this vector by another vector element-wise (compound assignment).
	 *
	 * @param v The vector to divide.
	 * @return A reference to this vector after division.
	 ***************************************************************************/
	Vector2f &operator/=(const Vector2f &v);

	/***************************************************************************
	 * @brief Adds a scalar value to each component of this vector (compound assignment).
	 *
	 * @param r The scalar value to add.
	 * @return A reference to this vector after addition.
	 ***************************************************************************/
	Vector2f &operator+=(const float r);

	/***************************************************************************
	 * @brief Subtracts a scalar value from each component of this vector (compound assignment).
	 *
	 * @param r The scalar value to subtract.
	 * @return A reference to this vector after subtraction.
	 ***************************************************************************/
	Vector2f &operator-=(const float r);

	/***************************************************************************
	 * @brief Multiplies each component of this vector by a scalar value (compound assignment).
	 *
	 * @param r The scalar value to multiply.
	 * @return A reference to this vector after multiplication.
	 ***************************************************************************/
	Vector2f &operator*=(const float r);

	/***************************************************************************
	 * @brief Divides each component of this vector by a scalar value (compound assignment).
	 *
	 * @param r The scalar value to divide.
	 * @return A reference to this vector after division.
	 ***************************************************************************/
	Vector2f &operator/=(const float r);

	/***************************************************************************
	 * @brief Compares this vector to another vector for equality.
	 *
	 * @param v The vector to compare with.
	 * @return True if the vectors are equal, false otherwise.
	 ***************************************************************************/
	bool operator==(const Vector2f &v) const noexcept;

	/***************************************************************************
	 * @brief Rotates the vector by a given angle.
	 *
	 * @param degrees The angle in degrees to rotate the vector.
	 * @return The rotated vector.
	 ***************************************************************************/
	Vector2f rotate(float degrees) const noexcept;
};

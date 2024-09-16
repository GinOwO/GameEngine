#include <math/Vector3f.h>

#include <math/Quaternion.h>

#include <cmath>
#include <array>

template <typename T> inline float to_degrees(T radians)
{
	return radians * (180.0 / M_PI);
}

/***************************************************************************
 * @brief Default constructor for Vector3f.
 *
 * Initializes the x, y, and z components to 0.
 ***************************************************************************/
Vector3f::Vector3f()
{
	x = y = z = 0;
}

/***************************************************************************
 * @brief Constructor for Vector3f with specified x, y, and z components.
 *
 * @param a The value for the x, y, and z components of the vector.
 ***************************************************************************/
Vector3f::Vector3f(float a)
{
	x = y = z = a;
}

/***************************************************************************
 * @brief Constructor for Vector3f with specified x, y, and z components.
 *
 * @param a The x component of the vector.
 * @param b The y component of the vector.
 * @param c The z component of the vector.
 ***************************************************************************/
Vector3f::Vector3f(float a, float b, float c)
{
	x = a;
	y = b;
	z = c;
}

/***************************************************************************
 * @brief Sets the x component of the vector.
 *
 * @param a The new x component of the vector.
 ***************************************************************************/
void Vector3f::setX(float a) noexcept
{
	this->x = a;
}

/***************************************************************************
 * @brief Sets the y component of the vector.
 *
 * @param b The new y component of the vector.
 ***************************************************************************/
void Vector3f::setY(float b) noexcept
{
	this->y = b;
}

/***************************************************************************
 * @brief Sets the z component of the vector.
 *
 * @param c The new z component of the vector.
 ***************************************************************************/
void Vector3f::setZ(float c) noexcept
{
	this->z = c;
}

/***************************************************************************
 * @brief Gets the x component of the vector.
 *
 * @return The x component of the vector.
 ***************************************************************************/
float Vector3f::getX() const noexcept
{
	return this->x;
}

/***************************************************************************
 * @brief Gets the y component of the vector.
 *
 * @return The y component of the vector.
 ***************************************************************************/
float Vector3f::getY() const noexcept
{
	return this->y;
}

/***************************************************************************
 * @brief Gets the z component of the vector.
 *
 * @return The z component of the vector.
 ***************************************************************************/
float Vector3f::getZ() const noexcept
{
	return this->z;
}

/***************************************************************************
 * @brief Gets the components of the vector as an array.
 *
 * @return An array containing the x, y, and z components of the vector.
 ***************************************************************************/
std::array<float, 3> Vector3f::get() const noexcept
{
	return { x, y, z };
}

/***************************************************************************
 * @brief Computes the length (magnitude) of the vector.
 *
 * @return The length of the vector.
 ***************************************************************************/
float Vector3f::length() const noexcept
{
	return std::sqrt(x * x + y * y + z * z);
}

/***************************************************************************
 * @brief Computes the dot product of this vector with another vector.
 *
 * @param v The vector to dot with.
 * @return The dot product of this vector and the given vector.
 ***************************************************************************/
float Vector3f::dot(const Vector3f &v) const noexcept
{
	return x * v.x + y * v.y + z * v.z;
}

/***************************************************************************
 * @brief Normalizes the vector.
 *
 * @return A normalized version of the vector. If the vector's length is 0,
 *	 a vector with the same components is returned.
 ***************************************************************************/
Vector3f Vector3f::normalize() const noexcept
{
	float len = length();
	if (len == 0)
		len = 1;
	return { x / len, y / len, z / len };
}

/***************************************************************************
 * @brief Adds another vector to this vector.
 *
 * @param v The vector to add.
 * @return The result of the addition.
 ***************************************************************************/
Vector3f Vector3f::operator+(const Vector3f &v) const noexcept
{
	return { x + v.x, y + v.y, z + v.z };
}

/***************************************************************************
 * @brief Subtracts another vector from this vector.
 *
 * @param v The vector to subtract.
 * @return The result of the subtraction.
 ***************************************************************************/
Vector3f Vector3f::operator-(const Vector3f &v) const noexcept
{
	return { x - v.x, y - v.y, z - v.z };
}

/***************************************************************************
 * @brief Multiplies this vector by another vector component-wise.
 *
 * @param v The vector to multiply by.
 * @return The result of the multiplication.
 ***************************************************************************/
Vector3f Vector3f::operator*(const Vector3f &v) const noexcept
{
	return { x * v.x, y * v.y, z * v.z };
}

/***************************************************************************
 * @brief Divides this vector by another vector component-wise.
 *
 * @param v The vector to divide by.
 * @return The result of the division.
 ***************************************************************************/
Vector3f Vector3f::operator/(const Vector3f &v) const noexcept
{
	return { x / v.x, y / v.y, z / v.z };
}

/***************************************************************************
 * @brief Adds a scalar to this vector.
 *
 * @param r The scalar to add.
 * @return The result of the addition.
 ***************************************************************************/
Vector3f Vector3f::operator+(const float r) const noexcept
{
	return { x + r, y + r, z + r };
}

/***************************************************************************
 * @brief Subtracts a scalar from this vector.
 *
 * @param r The scalar to subtract.
 * @return The result of the subtraction.
 ***************************************************************************/
Vector3f Vector3f::operator-(const float r) const noexcept
{
	return { x - r, y - r, z - r };
}

/***************************************************************************
 * @brief Multiplies this vector by a scalar.
 *
 * @param r The scalar to multiply by.
 * @return The result of the multiplication.
 ***************************************************************************/
Vector3f Vector3f::operator*(const float r) const noexcept
{
	return { x * r, y * r, z * r };
}

/***************************************************************************
 * @brief Divides this vector by a scalar.
 *
 * @param r The scalar to divide by.
 * @return The result of the division.
 ***************************************************************************/
Vector3f Vector3f::operator/(const float r) const noexcept
{
	return { x / r, y / r, z / r };
}

/***************************************************************************
 * @brief Adds another vector to this vector.
 *
 * @param v The vector to add.
 * @return The updated vector.
 ***************************************************************************/
Vector3f &Vector3f::operator+=(const Vector3f &v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

/***************************************************************************
 * @brief Subtracts another vector from this vector.
 *
 * @param v The vector to subtract.
 * @return The updated vector.
 ***************************************************************************/
Vector3f &Vector3f::operator-=(const Vector3f &v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

/***************************************************************************
 * @brief Multiplies this vector by another vector component-wise.
 *
 * @param v The vector to multiply by.
 * @return The updated vector.
 ***************************************************************************/
Vector3f &Vector3f::operator*=(const Vector3f &v)
{
	x *= v.x;
	y *= v.y;
	z *= v.z;
	return *this;
}

/***************************************************************************
 * @brief Divides this vector by another vector component-wise.
 *
 * @param v The vector to divide by.
 * @return The updated vector.
 ***************************************************************************/
Vector3f &Vector3f::operator/=(const Vector3f &v)
{
	x /= v.x;
	y /= v.y;
	z /= v.z;
	return *this;
}

/***************************************************************************
 * @brief Adds a scalar to this vector.
 *
 * @param r The scalar to add.
 * @return The updated vector.
 ***************************************************************************/
Vector3f &Vector3f::operator+=(const float r)
{
	x += r;
	y += r;
	z += r;
	return *this;
}

/***************************************************************************
 * @brief Subtracts a scalar from this vector.
 *
 * @param r The scalar to subtract.
 * @return The updated vector.
 ***************************************************************************/
Vector3f &Vector3f::operator-=(const float r)
{
	x -= r;
	y -= r;
	z -= r;
	return *this;
}

/***************************************************************************
 * @brief Multiplies this vector by a scalar.
 *
 * @param r The scalar to multiply by.
 * @return The updated vector.
 ***************************************************************************/
Vector3f &Vector3f::operator*=(const float r)
{
	x *= r;
	y *= r;
	z *= r;
	return *this;
}

/***************************************************************************
 * @brief Divides this vector by a scalar.
 *
 * @param r The scalar to divide by.
 * @return The updated vector.
 ***************************************************************************/
Vector3f &Vector3f::operator/=(const float r)
{
	x /= r;
	y /= r;
	z /= r;
	return *this;
}

/***************************************************************************
 * @brief Computes the cross product of this vector with another vector.
 *
 * @param v The vector to cross with.
 * @return The result of the cross product.
 ***************************************************************************/
Vector3f Vector3f::cross(const Vector3f &v) const noexcept
{
	return { y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x };
}

/***************************************************************************
 * @brief Rotates this vector around a specified axis by a given angle.
 *
 * @param angle The angle of rotation in degrees.
 * @param axis The axis around which to rotate.
 * @return The rotated vector.
 ***************************************************************************/
Vector3f Vector3f::rotate(const Vector3f &axis,
			  const float angle) const noexcept
{
	float sinAngle = std::sin(-angle);
	float cosAngle = std::cos(-angle);

	return this->cross(axis * sinAngle) +
	       (((*this) * (cosAngle)) +
		(axis * this->dot(axis * (1 - cosAngle))));
}

/***************************************************************************
 * @brief Compares this vector with another vector for equality.
 *
 * @param v The vector to compare with.
 * @return True if the vectors are equal, false otherwise.
 ***************************************************************************/
bool Vector3f::operator==(const Vector3f &v) const noexcept
{
	return this->x == v.x && this->y == v.y && this->z == v.z;
}

/***************************************************************************
 * @brief Interpolates between the current vector and a destination vector.
 *
 * This function computes the interpolation between the current vector and
 * a destination vector based on the given interpolation factor. The
 * interpolation is linear, and the factor determines the position of the
 * result between the two vectors. If the interpolation factor is 0.0, the
 * result will be the current vector. If the factor is 1.0, the result will
 * be the destination vector. Values between 0 and 1 will produce vectors
 * along the line segment between the two vectors.
 *
 * @param dest The destination vector to interpolate towards.
 * @param interpolation_factor The interpolation factor, typically in the
 *			     range [0.0, 1.0]. Values outside this range
 *			     will extrapolate beyond the start and end vectors.
 *
 * @return A new `Vector3f` that represents the interpolated vector.
 ***************************************************************************/
Vector3f Vector3f::interpolate(const Vector3f &dest,
			       float interpolation_factor) const noexcept
{
	return ((dest - *this) * interpolation_factor) + (*this);
}

/***************************************************************************
 * @brief Rotates the vector with a given Quaternion.
 *
 * @param quaternion The quaternion to rotate the vector as Array<float, 4>.
 * @return The rotated vector.
 ***************************************************************************/
Vector3f Vector3f::rotate(const std::array<float, 4> &quaternion) const noexcept
{
	Quaternion rotation = Quaternion{ quaternion[0], quaternion[1],
					  quaternion[2], quaternion[3] };
	Quaternion conjugate = rotation.conjugate();

	Quaternion w = (rotation * (*this)) * conjugate;

	return { w.getX(), w.getY(), w.getZ() };
}
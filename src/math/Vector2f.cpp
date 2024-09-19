#include <math/Vector2f.h>

#include <cmath>
#include <array>

template <typename T> inline float to_degrees(T radians)
{
	return radians * (180.0 / M_PI);
}

template <typename T> inline float to_radians(T degrees)
{
	return (degrees * M_PI) / 180.0;
}

/***************************************************************************
 * @brief Default constructor for Vector2f.
 *
 * Initializes the x and y components to 0.
 ***************************************************************************/
Vector2f::Vector2f()
{
	x = y = 0;
}

/***************************************************************************
 * @brief Constructor for Vector2f with specified x and y components.
 *
 * @param a The x component of the vector.
 * @param b The y component of the vector.
 ***************************************************************************/
Vector2f::Vector2f(float a, float b)
{
	x = a;
	y = b;
}

/***************************************************************************
 * @brief Sets the x component of the vector.
 *
 * @param a The new x component of the vector.
 ***************************************************************************/
void Vector2f::setX(float a) noexcept
{
	this->x = a;
}

/***************************************************************************
 * @brief Sets the y component of the vector.
 *
 * @param b The new y component of the vector.
 ***************************************************************************/
void Vector2f::setY(float b) noexcept
{
	this->y = b;
}

/***************************************************************************
 * @brief Gets the x component of the vector.
 *
 * @return The x component of the vector.
 ***************************************************************************/
float Vector2f::getX() const noexcept
{
	return this->x;
}

/***************************************************************************
 * @brief Gets the y component of the vector.
 *
 * @return The y component of the vector.
 ***************************************************************************/
float Vector2f::getY() const noexcept
{
	return this->y;
}

/***************************************************************************
 * @brief Gets the components of the vector as an array.
 *
 * @return An array containing the x and y components of the vector.
 ***************************************************************************/
std::array<float, 2> Vector2f::get() const noexcept
{
	return { x, y };
}

/***************************************************************************
 * @brief Computes the length (magnitude) of the vector.
 *
 * @return The length of the vector.
 ***************************************************************************/
float Vector2f::length() const noexcept
{
	return std::sqrt(x * x + y * y);
}

/***************************************************************************
 * @brief Computes the dot product of this vector with another vector.
 *
 * @param v The vector to dot with.
 * @return The dot product of this vector and the given vector.
 ***************************************************************************/
float Vector2f::dot(const Vector2f &v) const noexcept
{
	return x * v.x + y * v.y;
}

/***************************************************************************
 * @brief Normalizes the vector.
 *
 * @return A normalized version of the vector.
 ***************************************************************************/
Vector2f Vector2f::normalize() const noexcept
{
	float len = length();
	return { x / len, y / len };
}

/***************************************************************************
 * @brief Adds another vector to this vector.
 *
 * @param v The vector to add.
 * @return The result of the addition.
 ***************************************************************************/
Vector2f Vector2f::operator+(const Vector2f &v) const noexcept
{
	return { x + v.x, y + v.y };
}

/***************************************************************************
 * @brief Subtracts another vector from this vector.
 *
 * @param v The vector to subtract.
 * @return The result of the subtraction.
 ***************************************************************************/
Vector2f Vector2f::operator-(const Vector2f &v) const noexcept
{
	return { x - v.x, y - v.y };
}

/***************************************************************************
 * @brief Multiplies this vector by another vector component-wise.
 *
 * @param v The vector to multiply by.
 * @return The result of the multiplication.
 ***************************************************************************/
Vector2f Vector2f::operator*(const Vector2f &v) const noexcept
{
	return { x * v.x, y * v.y };
}

/***************************************************************************
 * @brief Divides this vector by another vector component-wise.
 *
 * @param v The vector to divide by.
 * @return The result of the division.
 ***************************************************************************/
Vector2f Vector2f::operator/(const Vector2f &v) const noexcept
{
	return { x / v.x, y / v.y };
}

/***************************************************************************
 * @brief Adds a scalar to this vector.
 *
 * @param r The scalar to add.
 * @return The result of the addition.
 ***************************************************************************/
Vector2f Vector2f::operator+(const float r) const noexcept
{
	return { x + r, y + r };
}

/***************************************************************************
 * @brief Subtracts a scalar from this vector.
 *
 * @param r The scalar to subtract.
 * @return The result of the subtraction.
 ***************************************************************************/
Vector2f Vector2f::operator-(const float r) const noexcept
{
	return { x - r, y - r };
}

/***************************************************************************
 * @brief Multiplies this vector by a scalar.
 *
 * @param r The scalar to multiply by.
 * @return The result of the multiplication.
 ***************************************************************************/
Vector2f Vector2f::operator*(const float r) const noexcept
{
	return { x * r, y * r };
}

/***************************************************************************
 * @brief Divides this vector by a scalar.
 *
 * @param r The scalar to divide by.
 * @return The result of the division.
 ***************************************************************************/
Vector2f Vector2f::operator/(const float r) const noexcept
{
	return { x / r, y / r };
}

/***************************************************************************
 * @brief Adds another vector to this vector.
 *
 * @param v The vector to add.
 * @return The updated vector.
 ***************************************************************************/
Vector2f &Vector2f::operator+=(const Vector2f &v)
{
	x += v.x;
	y += v.y;
	return *this;
}

/***************************************************************************
 * @brief Subtracts another vector from this vector.
 *
 * @param v The vector to subtract.
 * @return The updated vector.
 ***************************************************************************/
Vector2f &Vector2f::operator-=(const Vector2f &v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}

/***************************************************************************
 * @brief Multiplies this vector by another vector component-wise.
 *
 * @param v The vector to multiply by.
 * @return The updated vector.
 ***************************************************************************/
Vector2f &Vector2f::operator*=(const Vector2f &v)
{
	x *= v.x;
	y *= v.y;
	return *this;
}

/***************************************************************************
 * @brief Divides this vector by another vector component-wise.
 *
 * @param v The vector to divide by.
 * @return The updated vector.
 ***************************************************************************/
Vector2f &Vector2f::operator/=(const Vector2f &v)
{
	x /= v.x;
	y /= v.y;
	return *this;
}

/***************************************************************************
 * @brief Adds a scalar to this vector.
 *
 * @param r The scalar to add.
 * @return The updated vector.
 ***************************************************************************/
Vector2f &Vector2f::operator+=(const float r)
{
	x += r;
	y += r;
	return *this;
}

/***************************************************************************
 * @brief Subtracts a scalar from this vector.
 *
 * @param r The scalar to subtract.
 * @return The updated vector.
 ***************************************************************************/
Vector2f &Vector2f::operator-=(const float r)
{
	x -= r;
	y -= r;
	return *this;
}

/***************************************************************************
 * @brief Multiplies this vector by a scalar.
 *
 * @param r The scalar to multiply by.
 * @return The updated vector.
 ***************************************************************************/
Vector2f &Vector2f::operator*=(const float r)
{
	x *= r;
	y *= r;
	return *this;
}

/***************************************************************************
 * @brief Divides this vector by a scalar.
 *
 * @param r The scalar to divide by.
 * @return The updated vector.
 ***************************************************************************/
Vector2f &Vector2f::operator/=(const float r)
{
	x /= r;
	y /= r;
	return *this;
}

/***************************************************************************
 * @brief Rotates the vector by a specified angle in degrees.
 *
 * @param degrees The angle to rotate by, in degrees.
 * @return The rotated vector.
 ***************************************************************************/
Vector2f Vector2f::rotate(float degrees) const noexcept
{
	float rad = to_radians(degrees);
	float c = cos(rad);
	float s = sin(rad);

	return { x * c - y * s, x * s + y * c };
}

/***************************************************************************
 * @brief Interpolates between the current vector and a destination vector.
 *
 * @param dest The destination vector to interpolate towards.
 * @param interpolation_factor The interpolation factor, typically in the
 *			     range [0.0, 1.0]. Values outside this range
 *			     will extrapolate beyond the start and end vectors.
 *
 * @return A new `Vector2f` that represents the interpolated vector.
 ***************************************************************************/
Vector2f Vector2f::lerp(const Vector2f &dest,
			float interpolation_factor) const noexcept
{
	return ((dest - *this) * interpolation_factor) + (*this);
}

/***************************************************************************
 * @brief Computes the cross product of the current vector with another vector.
 *
 * @param v The vector to compute the cross product with.
 *
 * @return The scalar result of the cross product.
 ***************************************************************************/
float Vector2f::cross(const Vector2f &v) const noexcept
{
	return x * v.y - y * v.x;
}
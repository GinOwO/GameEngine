#include <math/Vector3f.h>

#include <math/Quaternion.h>

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

Vector3f::Vector3f()
{
	x = y = z = 0;
}

Vector3f::Vector3f(float a, float b, float c)
{
	x = a;
	y = b;
	z = c;
}

void Vector3f::setX(float a) noexcept
{
	this->x = a;
}

void Vector3f::setY(float b) noexcept
{
	this->y = b;
}

void Vector3f::setZ(float c) noexcept
{
	this->z = c;
}

float Vector3f::getX() const noexcept
{
	return this->x;
}

float Vector3f::getY() const noexcept
{
	return this->y;
}

float Vector3f::getZ() const noexcept
{
	return this->z;
}

std::array<float, 3> Vector3f::get() const noexcept
{
	return { x, y, z };
}

float Vector3f::length() const noexcept
{
	return std::sqrt(x * x + y * y + z * z);
}

float Vector3f::dot(const Vector3f &v) noexcept
{
	return x * v.x + y * v.y + z * v.z;
}

Vector3f Vector3f::normalize() const noexcept
{
	float len = length();
	if (len == 0)
		len = 1;
	return { x / len, y / len, z / len };
}

Vector3f Vector3f::operator+(const Vector3f &v) const noexcept
{
	return { x + v.x, y + v.y, z + v.z };
}

Vector3f Vector3f::operator-(const Vector3f &v) const noexcept
{
	return { x - v.x, y - v.y, z - v.z };
}

Vector3f Vector3f::operator*(const Vector3f &v) const noexcept
{
	return { x * v.x, y * v.y, z * v.z };
}

Vector3f Vector3f::operator/(const Vector3f &v) const noexcept
{
	return { x / v.x, y / v.y, z / v.z };
}

Vector3f Vector3f::operator+(const float r) const noexcept
{
	return { x + r, y + r, z + r };
}

Vector3f Vector3f::operator-(const float r) const noexcept
{
	return { x - r, y - r, z - r };
}

Vector3f Vector3f::operator*(const float r) const noexcept
{
	return { x * r, y * r, z * r };
}

Vector3f Vector3f::operator/(const float r) const noexcept
{
	return { x / r, y / r, z / r };
}

Vector3f &Vector3f::operator+=(const Vector3f &v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

Vector3f &Vector3f::operator-=(const Vector3f &v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

Vector3f &Vector3f::operator*=(const Vector3f &v)
{
	x *= v.x;
	y *= v.y;
	z *= v.z;
	return *this;
}

Vector3f &Vector3f::operator/=(const Vector3f &v)
{
	x /= v.x;
	y /= v.y;
	z /= v.z;
	return *this;
}

Vector3f &Vector3f::operator+=(const float r)
{
	x += r;
	y += r;
	z += r;
	return *this;
}

Vector3f &Vector3f::operator-=(const float r)
{
	x -= r;
	y -= r;
	z -= r;
	return *this;
}

Vector3f &Vector3f::operator*=(const float r)
{
	x *= r;
	y *= r;
	z *= r;
	return *this;
}

Vector3f &Vector3f::operator/=(const float r)
{
	x /= r;
	y /= r;
	z /= r;
	return *this;
}

Vector3f Vector3f::cross(const Vector3f &v) const noexcept
{
	return { y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x };
}

Vector3f Vector3f::rotate(const float angle,
			  const Vector3f &axis) const noexcept
{
	// Convert angle from degrees to radians
	float rad_angle = to_radians(angle);
	float sin_half_angle = std::sin(rad_angle / 2.0f);
	float cos_half_angle = std::cos(rad_angle / 2.0f);

	// Create the rotation quaternion
	Quaternion rotation{ axis.getX() * sin_half_angle,
			     axis.getY() * sin_half_angle,
			     axis.getZ() * sin_half_angle, cos_half_angle };

	// Create a quaternion for the vector to be rotated
	Quaternion v_as_quat{ this->x, this->y, this->z, 0.0f };

	// Perform rotation: q * v * q^*
	Quaternion rotated = rotation * v_as_quat * rotation.conjugate();

	return { rotated.getX(), rotated.getY(), rotated.getZ() };
}

bool Vector3f::operator==(const Vector3f &v) const noexcept
{
	return this->x == v.x && this->y == v.y && this->z == v.z;
}
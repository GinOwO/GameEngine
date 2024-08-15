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
	return std::sqrtl(x * x + y * y + z * z);
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
	float sin_half_angle = std::sinf(to_radians(angle / 2.0f));
	float cos_half_angle = std::cosf(to_radians(angle / 2.0f));

	Quaternion rotation{ axis.getX() * sin_half_angle,
			     axis.getY() * sin_half_angle,
			     axis.getZ() * sin_half_angle, cos_half_angle };

	Quaternion w = (rotation * (*this)) * rotation.conjugate();

	return { w.getX(), w.getY(), w.getZ() };
}
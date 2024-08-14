#include <Math/Vector3f.h>

#include <cmath>
#include <array>

const float PI = 3.14159;

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

Vector3f Vector3f::normalize()
{
	float len = length();
	return { x / len, y / len, z / len };
}

Vector3f Vector3f::operator+(const Vector3f &v)
{
	return { x + v.x, y + v.y, z + v.z };
}

Vector3f Vector3f::operator-(const Vector3f &v)
{
	return { x - v.x, y - v.y, z - v.z };
}

Vector3f Vector3f::operator*(const Vector3f &v)
{
	return { x * v.x, y * v.y, z * v.z };
}

Vector3f Vector3f::operator/(const Vector3f &v)
{
	return { x / v.x, y / v.y, z / v.z };
}

Vector3f Vector3f::operator+(const float r)
{
	return { x + r, y + r, z + r };
}

Vector3f Vector3f::operator-(const float r)
{
	return { x - r, y - r, z - r };
}

Vector3f Vector3f::operator*(const float r)
{
	return { x * r, y * r, z * r };
}

Vector3f Vector3f::operator/(const float r)
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
#include <Vector3f.h>

#include <cmath>
#include <array>

const double PI = 3.14159;

Vector3f::Vector3f()
{
	x = y = z = 0;
}

Vector3f::Vector3f(double a, double b, double c)
{
	x = a;
	y = b;
	z = c;
}

void Vector3f::setX(double a) noexcept
{
	this->x = a;
}

void Vector3f::setY(double b) noexcept
{
	this->y = b;
}

void Vector3f::setZ(double c) noexcept
{
	this->z = c;
}

double Vector3f::getX() const noexcept
{
	return this->x;
}

double Vector3f::getY() const noexcept
{
	return this->y;
}

double Vector3f::getZ() const noexcept
{
	return this->z;
}

std::array<double, 3> Vector3f::get() const noexcept
{
	return { x, y, z };
}

double Vector3f::length() const noexcept
{
	return std::sqrtl(x * x + y * y + z * z);
}

double Vector3f::dot(const Vector3f &v) noexcept
{
	return x * v.x + y * v.y + z * v.z;
}

Vector3f Vector3f::normalize()
{
	double len = length();
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

Vector3f Vector3f::operator+(const double r)
{
	return { x + r, y + r, z + r };
}

Vector3f Vector3f::operator-(const double r)
{
	return { x - r, y - r, z - r };
}

Vector3f Vector3f::operator*(const double r)
{
	return { x * r, y * r, z * r };
}

Vector3f Vector3f::operator/(const double r)
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

Vector3f &Vector3f::operator+=(const double r)
{
	x += r;
	y += r;
	z += r;
	return *this;
}

Vector3f &Vector3f::operator-=(const double r)
{
	x -= r;
	y -= r;
	z -= r;
	return *this;
}

Vector3f &Vector3f::operator*=(const double r)
{
	x *= r;
	y *= r;
	z *= r;
	return *this;
}

Vector3f &Vector3f::operator/=(const double r)
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
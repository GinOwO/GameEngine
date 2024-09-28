#include <math/Vector3f.h>

#include <math/Quaternion.h>

#include <cmath>
#include <array>

template <typename T> inline float to_degrees(T radians)
{
	return radians * (180.0 / M_PI);
}

const std::function<void(void *)> Vector3f::deleter{ [](void *ptr) {
	delete static_cast<Vector3f *>(ptr);
} };

const Vector3f Vector3f::x_axis{ 1, 0, 0 };
const Vector3f Vector3f::y_axis{ 0, 1, 0 };
const Vector3f Vector3f::z_axis{ 0, 0, 1 };

Vector3f::Vector3f()
{
	x = y = z = 0;
}

Vector3f::Vector3f(float a)
{
	x = y = z = a;
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

float Vector3f::dot(const Vector3f &v) const noexcept
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

Vector3f Vector3f::rotate(const Vector3f &axis,
			  const float angle) const noexcept
{
	float sinAngle = std::sin(-angle);
	float cosAngle = std::cos(-angle);

	return this->cross(axis * sinAngle) +
	       (((*this) * (cosAngle)) +
		(axis * this->dot(axis * (1 - cosAngle))));
}

Vector3f Vector3f::lerp(const Vector3f &dest,
			float interpolation_factor) const noexcept
{
	return ((dest - *this) * interpolation_factor) + (*this);
}

Vector3f Vector3f::rotate(const std::array<float, 4> &quaternion) const noexcept
{
	Quaternion rotation = Quaternion{ quaternion[0], quaternion[1],
					  quaternion[2], quaternion[3] };
	Quaternion conjugate = rotation.conjugate();

	Quaternion w = (rotation * (*this)) * conjugate;

	return { w.getX(), w.getY(), w.getZ() };
}

bool Vector3f::is_close(const Vector3f &other, float tolerance) const noexcept
{
	return (std::abs(other.x - x) <= tolerance) &&
	       (std::abs(other.y - y) <= tolerance) &&
	       (std::abs(other.y - y) <= tolerance);
}
#include <Quaternion.h>

#include <Vector3f.h>

#include <cmath>

const float PI = 3.14159;

Quaternion::Quaternion()
{
	x = y = z = w = 0;
}

Quaternion::Quaternion(float a, float b, float c, float d)
{
	x = a;
	y = b;
	z = c;
	w = d;
}

void Quaternion::setX(float a) noexcept
{
	this->x = a;
}

void Quaternion::setY(float b) noexcept
{
	this->y = b;
}

void Quaternion::setZ(float c) noexcept
{
	this->z = c;
}

void Quaternion::setW(float d) noexcept
{
	this->w = d;
}

float Quaternion::getX() const noexcept
{
	return this->x;
}

float Quaternion::getY() const noexcept
{
	return this->y;
}

float Quaternion::getZ() const noexcept
{
	return this->z;
}

float Quaternion::getW() const noexcept
{
	return this->w;
}

float Quaternion::length() const noexcept
{
	return std::sqrtl(x * x + y * y + z * z + w * w);
}

Quaternion Quaternion::normalize()
{
	float len = length();
	return { x / len, y / len, z / len, w / len };
}

Quaternion Quaternion::conjugate()
{
	return { -x, -y, -z, w };
}

Quaternion Quaternion::operator+(const Quaternion &v)
{
	return { x + v.x, y + v.y, z + v.z, w + v.w };
}

Quaternion Quaternion::operator-(const Quaternion &v)
{
	return { x - v.x, y - v.y, z - v.z, w - v.w };
}

Quaternion Quaternion::operator*(const Quaternion &v)
{
	return { x * v.y + w * v.x + y * v.z - z * v.y,
		 y * v.w + w * v.y + z * v.x - x * v.z,
		 w * v.w + w * v.z + x * v.y - y * v.x,
		 w * v.w - x * v.x - y * v.y - z * v.z };
}

Quaternion Quaternion::operator*(const Vector3f &v)
{
	return { w * v.getX() + y * v.getZ() - z * v.getY(),
		 w * v.getY() + z * v.getX() - x * v.getZ(),
		 w * v.getZ() + x * v.getY() - y * v.getX(),
		 -x * v.getX() - y * v.getY() - z * v.getZ() };
}

Quaternion Quaternion::operator/(const Quaternion &v)
{
	return { x / v.x, y / v.y, z / v.z, w / v.w };
}

Quaternion Quaternion::operator+(const float r)
{
	return { x + r, y + r, z + r, w + r };
}

Quaternion Quaternion::operator-(const float r)
{
	return { x - r, y - r, z - r, w - r };
}

Quaternion Quaternion::operator*(const float r)
{
	return { x * r, y * r, z * r, w * r };
}

Quaternion Quaternion::operator/(const float r)
{
	return { x / r, y / r, z / r, w / r };
}

Quaternion &Quaternion::operator+=(const Quaternion &v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	w += v.w;
	return *this;
}

Quaternion &Quaternion::operator-=(const Quaternion &v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	w -= v.w;
	return *this;
}

Quaternion &Quaternion::operator*=(const Quaternion &v)
{
	float a = x * v.y + w * v.x + y * v.z - z * v.y,
	      b = y * v.w + w * v.y + z * v.x - x * v.z,
	      c = w * v.w + w * v.z + x * v.y - y * v.x,
	      d = w * v.w - x * v.x - y * v.y - z * v.z;
	x = a;
	y = b;
	z = c;
	w = d;
	return *this;
}

Quaternion &Quaternion::operator*=(const Vector3f &v)
{
	float a = w * v.getX() + y * v.getZ() - z * v.getY(),
	      b = w * v.getY() + z * v.getX() - x * v.getZ(),
	      c = w * v.getZ() + x * v.getY() - y * v.getX(),
	      d = -x * v.getX() - y * v.getY() - z * v.getZ();

	x = a;
	y = b;
	z = c;
	w = d;
	return *this;
}

Quaternion &Quaternion::operator/=(const Quaternion &v)
{
	x /= v.x;
	y /= v.y;
	z /= v.z;
	w /= v.w;
	return *this;
}

Quaternion &Quaternion::operator+=(const float r)
{
	x += r;
	y += r;
	z += r;
	w += r;
	return *this;
}

Quaternion &Quaternion::operator-=(const float r)
{
	x -= r;
	y -= r;
	z -= r;
	w -= r;
	return *this;
}

Quaternion &Quaternion::operator*=(const float r)
{
	x *= r;
	y *= r;
	z *= r;
	w *= r;
	return *this;
}

Quaternion &Quaternion::operator/=(const float r)
{
	x /= r;
	y /= r;
	z /= r;
	w /= r;
	return *this;
}

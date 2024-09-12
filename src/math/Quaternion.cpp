#include <math/Quaternion.h>

#include <cmath>

#include <math/Vector3f.h>

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
	return std::sqrt(x * x + y * y + z * z + w * w);
}

Quaternion Quaternion::normalize() const noexcept
{
	float len = length();
	if (len == 0)
		len = 1;
	return { x / len, y / len, z / len, w / len };
}

Quaternion Quaternion::conjugate() const noexcept
{
	return { -x, -y, -z, w };
}

Quaternion Quaternion::operator+(const Quaternion &v) const noexcept
{
	return { x + v.x, y + v.y, z + v.z, w + v.w };
}

Quaternion Quaternion::operator-(const Quaternion &v) const noexcept
{
	return { x - v.x, y - v.y, z - v.z, w - v.w };
}

Quaternion Quaternion::operator*(const Quaternion &v) const noexcept
{
	return { w * v.x + x * v.w + y * v.z - z * v.y,
		 w * v.y - x * v.z + y * v.w + z * v.x,
		 w * v.z + x * v.y - y * v.x + z * v.w,
		 w * v.w - x * v.x - y * v.y - z * v.z };
}

Quaternion Quaternion::operator*(const Vector3f &v) const noexcept
{
	return { w * v.getX() + y * v.getZ() - z * v.getY(),
		 w * v.getY() + z * v.getX() - x * v.getZ(),
		 w * v.getZ() + x * v.getY() - y * v.getX(),
		 -x * v.getX() - y * v.getY() - z * v.getZ() };
}

Quaternion Quaternion::operator/(const Quaternion &v) const noexcept
{
	return { x / v.x, y / v.y, z / v.z, w / v.w };
}

Quaternion Quaternion::operator+(const float r) const noexcept
{
	return { x + r, y + r, z + r, w + r };
}

Quaternion Quaternion::operator-(const float r) const noexcept
{
	return { x - r, y - r, z - r, w - r };
}

Quaternion Quaternion::operator*(const float r) const noexcept
{
	return { x * r, y * r, z * r, w * r };
}

Quaternion Quaternion::operator/(const float r) const noexcept
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

bool Quaternion::operator==(const Quaternion &q) const noexcept
{
	return this->x == q.x && this->y == q.y && this->z == q.z &&
	       this->w == q.w;
}
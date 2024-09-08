#include <math/Vector2f.h>

#include <cmath>
#include <array>

const float PI = 3.14159;

Vector2f::Vector2f()
{
	x = y = 0;
}

Vector2f::Vector2f(float a, float b)
{
	x = a;
	y = b;
}

void Vector2f::setX(float a) noexcept
{
	this->x = a;
}

void Vector2f::setY(float b) noexcept
{
	this->y = b;
}

float Vector2f::getX() const noexcept
{
	return this->x;
}

float Vector2f::getY() const noexcept
{
	return this->y;
}

std::array<float, 2> Vector2f::get() const noexcept
{
	return { x, y };
}

float Vector2f::length() const noexcept
{
	return std::sqrt(x * x + y * y);
}

float Vector2f::dot(const Vector2f &v) const noexcept
{
	return x * v.x + y * v.y;
}

Vector2f Vector2f::normalize() const noexcept
{
	float len = length();
	return { x / len, y / len };
}

Vector2f Vector2f::operator+(const Vector2f &v) const noexcept
{
	return { x + v.x, y + v.y };
}

Vector2f Vector2f::operator-(const Vector2f &v) const noexcept
{
	return { x - v.x, y - v.y };
}

Vector2f Vector2f::operator*(const Vector2f &v) const noexcept
{
	return { x * v.x, y * v.y };
}

Vector2f Vector2f::operator/(const Vector2f &v) const noexcept
{
	return { x / v.x, y / v.y };
}

Vector2f Vector2f::operator+(const float r) const noexcept
{
	return { x + r, y + r };
}

Vector2f Vector2f::operator-(const float r) const noexcept
{
	return { x - r, y - r };
}

Vector2f Vector2f::operator*(const float r) const noexcept
{
	return { x * r, y * r };
}

Vector2f Vector2f::operator/(const float r) const noexcept
{
	return { x / r, y / r };
}

Vector2f &Vector2f::operator+=(const Vector2f &v)
{
	x += v.x;
	y += v.y;
	return *this;
}

Vector2f &Vector2f::operator-=(const Vector2f &v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}

Vector2f &Vector2f::operator*=(const Vector2f &v)
{
	x *= v.x;
	y *= v.y;
	return *this;
}

Vector2f &Vector2f::operator/=(const Vector2f &v)
{
	x /= v.x;
	y /= v.y;
	return *this;
}

Vector2f &Vector2f::operator+=(const float r)
{
	x += r;
	y += r;
	return *this;
}

Vector2f &Vector2f::operator-=(const float r)
{
	x -= r;
	y -= r;
	return *this;
}

Vector2f &Vector2f::operator*=(const float r)
{
	x *= r;
	y *= r;
	return *this;
}

Vector2f &Vector2f::operator/=(const float r)
{
	x /= r;
	y /= r;
	return *this;
}

bool Vector2f::operator==(const Vector2f &v) const noexcept
{
	return this->x == v.x && this->y == v.y;
}

Vector2f Vector2f::rotate(float degrees) const noexcept
{
	float rad = degrees * (PI / 180);
	float c = cos(rad);
	float s = sin(rad);

	return { x * c - y * s, x * s + y * c };
}
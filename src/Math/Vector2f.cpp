#include <Vector2f.h>

#include <cmath>

const double PI = 3.14159;

Vector2f::Vector2f()
{
	x = y = 0;
}

Vector2f::Vector2f(double a, double b)
{
	x = a;
	y = b;
}

void Vector2f::setX(double a) noexcept
{
	this->x = a;
}

void Vector2f::setY(double b) noexcept
{
	this->y = b;
}

double Vector2f::getX() const noexcept
{
	return this->x;
}

double Vector2f::getY() const noexcept
{
	return this->y;
}

double Vector2f::length() const noexcept
{
	return std::sqrtl(x * x + y * y);
}

double Vector2f::dot(const Vector2f &v) noexcept
{
	return x * v.x + y * v.y;
}

Vector2f Vector2f::normalize()
{
	double len = length();
	return { x / len, y / len };
}

Vector2f Vector2f::operator+(const Vector2f &v)
{
	return { x + v.x, y + v.y };
}

Vector2f Vector2f::operator-(const Vector2f &v)
{
	return { x - v.x, y - v.y };
}

Vector2f Vector2f::operator*(const Vector2f &v)
{
	return { x * v.x, y * v.y };
}

Vector2f Vector2f::operator/(const Vector2f &v)
{
	return { x / v.x, y / v.y };
}

Vector2f Vector2f::operator+(const double r)
{
	return { x + r, y + r };
}

Vector2f Vector2f::operator-(const double r)
{
	return { x - r, y - r };
}

Vector2f Vector2f::operator*(const double r)
{
	return { x * r, y * r };
}

Vector2f Vector2f::operator/(const double r)
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

Vector2f &Vector2f::operator+=(const double r)
{
	x += r;
	y += r;
	return *this;
}

Vector2f &Vector2f::operator-=(const double r)
{
	x -= r;
	y -= r;
	return *this;
}

Vector2f &Vector2f::operator*=(const double r)
{
	x *= r;
	y *= r;
	return *this;
}

Vector2f &Vector2f::operator/=(const double r)
{
	x /= r;
	y /= r;
	return *this;
}

Vector2f Vector2f::rotate(double degrees) const noexcept
{
	double rad = degrees * (PI / 180);
	double c = cos(rad);
	double s = sin(rad);

	return { x * c - y * s, x * s + y * c };
}
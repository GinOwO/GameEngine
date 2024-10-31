#pragma once

#include <cstdint>
#include <array>

class Vector2f {
    private:
	float x;
	float y;

    public:
	Vector2f();

	Vector2f(float a, float b);

	void setX(float a) noexcept;

	void setY(float b) noexcept;

	float getX() const noexcept;

	float getY() const noexcept;

	std::array<float, 2> get() const noexcept;

	float length() const noexcept;

	float dot(const Vector2f &v) const noexcept;

	Vector2f normalize() const noexcept;

	Vector2f operator+(const Vector2f &v) const noexcept;

	Vector2f operator-(const Vector2f &v) const noexcept;

	Vector2f operator*(const Vector2f &v) const noexcept;

	Vector2f operator/(const Vector2f &v) const noexcept;

	Vector2f operator+(const float r) const noexcept;

	Vector2f operator-(const float r) const noexcept;

	Vector2f operator*(const float r) const noexcept;

	Vector2f operator/(const float r) const noexcept;

	Vector2f &operator+=(const Vector2f &v);

	Vector2f &operator-=(const Vector2f &v);

	Vector2f &operator*=(const Vector2f &v);

	Vector2f &operator/=(const Vector2f &v);

	Vector2f &operator+=(const float r);

	Vector2f &operator-=(const float r);

	Vector2f &operator*=(const float r);

	Vector2f &operator/=(const float r);

	constexpr bool operator==(const Vector2f &v) const noexcept
	{
		return this->x == v.x && this->y == v.y;
	}

	Vector2f rotate(float degrees) const noexcept;

	Vector2f lerp(const Vector2f &dest,
		      float interpolation_factor) const noexcept;

	float cross(const Vector2f &v) const noexcept;
};

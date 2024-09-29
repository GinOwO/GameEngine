#pragma once

#include <array>
#include <cmath>
#include <functional>
#include <iostream>

class Vector3f {
    private:
	float x;
	float y;
	float z;

    public:
	static const std::function<void(void *)> deleter;
	static const Vector3f x_axis;
	static const Vector3f y_axis;
	static const Vector3f z_axis;

	Vector3f();

	Vector3f(float a);

	Vector3f(float a, float b, float c);

	void setX(float a) noexcept;

	void setY(float b) noexcept;

	void setZ(float c) noexcept;

	float getX() const noexcept;

	float getY() const noexcept;

	float getZ() const noexcept;

	std::array<float, 3> get() const noexcept;

	float length() const noexcept;

	float dot(const Vector3f &v) const noexcept;

	Vector3f normalize() const noexcept;

	Vector3f operator+(const Vector3f &v) const noexcept;

	Vector3f operator-(const Vector3f &v) const noexcept;

	Vector3f operator*(const Vector3f &v) const noexcept;

	Vector3f operator/(const Vector3f &v) const noexcept;

	Vector3f operator+(const float r) const noexcept;

	Vector3f operator-(const float r) const noexcept;

	Vector3f operator*(const float r) const noexcept;

	Vector3f operator/(const float r) const noexcept;

	Vector3f &operator+=(const Vector3f &v);

	Vector3f &operator-=(const Vector3f &v);

	Vector3f &operator*=(const Vector3f &v);

	Vector3f &operator/=(const Vector3f &v);

	Vector3f &operator+=(const float r);

	Vector3f &operator-=(const float r);

	Vector3f &operator*=(const float r);

	Vector3f &operator/=(const float r);

	constexpr bool operator==(const Vector3f &v) const noexcept
	{
		return this->x == v.x && this->y == v.y && this->z == v.z;
	}

	Vector3f cross(const Vector3f &v) const noexcept;

	Vector3f rotate(const Vector3f &axis, const float angle) const noexcept;

	Vector3f rotate(const std::array<float, 4> &quaternion) const noexcept;

	Vector3f lerp(const Vector3f &dest,
		      float interpolation_factor) const noexcept;

	bool is_close(const Vector3f &other,
		      float tolerance = 1e-6) const noexcept;

	friend std::ostream &operator<<(std::ostream &os, const Vector3f &v);
};

template <typename T> inline float to_radians(T degrees)
{
	return (degrees * M_PI) / 180.0;
}
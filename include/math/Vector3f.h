#pragma once

#include <array>
class Vector3f {
    private:
	float x;
	float y;
	float z;

    public:
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
	float dot(const Vector3f &v) noexcept;
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

	bool operator==(const Vector3f &v) const noexcept;

	Vector3f cross(const Vector3f &v) const noexcept;
	Vector3f rotate(const float angle, const Vector3f &axis) const noexcept;
};
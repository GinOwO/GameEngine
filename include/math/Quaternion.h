#pragma once

#include <math/Vector3f.h>

class Quaternion {
    private:
	float x;
	float y;
	float z;
	float w;

    public:
	Quaternion();
	Quaternion(float a, float b, float c, float d);

	void setX(float a) noexcept;
	void setY(float b) noexcept;
	void setZ(float c) noexcept;
	void setW(float d) noexcept;
	float getX() const noexcept;
	float getY() const noexcept;
	float getZ() const noexcept;
	float getW() const noexcept;

	float length() const noexcept;
	Quaternion normalize() const noexcept;
	Quaternion conjugate() const noexcept;

	Quaternion operator+(const Quaternion &v) const noexcept;
	Quaternion operator-(const Quaternion &v) const noexcept;
	Quaternion operator*(const Quaternion &v) const noexcept;
	Quaternion operator*(const Vector3f &v) const noexcept;
	Quaternion operator/(const Quaternion &v) const noexcept;
	Quaternion operator+(const float r) const noexcept;
	Quaternion operator-(const float r) const noexcept;
	Quaternion operator*(const float r) const noexcept;
	Quaternion operator/(const float r) const noexcept;

	Quaternion &operator+=(const Quaternion &v);
	Quaternion &operator-=(const Quaternion &v);
	Quaternion &operator*=(const Quaternion &v);
	Quaternion &operator*=(const Vector3f &v);
	Quaternion &operator/=(const Quaternion &v);
	Quaternion &operator+=(const float r);
	Quaternion &operator-=(const float r);
	Quaternion &operator*=(const float r);
	Quaternion &operator/=(const float r);
};
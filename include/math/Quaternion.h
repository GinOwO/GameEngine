#pragma once

#include <math/Vector3f.h>
#include <math/Matrix4f.h>

#include <array>

class Quaternion {
    private:
	float x;
	float y;
	float z;
	float w;

    public:
	Vector3f get_forward() const;

	Vector3f get_backward() const;

	Vector3f get_up() const;

	Vector3f get_down() const;

	Vector3f get_right() const;

	Vector3f get_left() const;

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

	std::array<float, 4> get() const noexcept;

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

	constexpr bool operator==(const Quaternion &q) const noexcept
	{
		return this->x == q.x && this->y == q.y && this->z == q.z &&
		       this->w == q.w;
	}

	Matrix4f to_rotation_matrix() const noexcept;
	static Quaternion Rotation_Quaternion(const Vector3f &axis,
					      float angle) noexcept;
	Quaternion(const Matrix4f &matrix);
	float dot(const Quaternion &r) const noexcept;
	Quaternion nlerp(Quaternion dest, float lerpFactor,
			 bool shortest = false);
	Quaternion slerp(Quaternion dest, float lerpFactor,
			 bool shortest = false);
};

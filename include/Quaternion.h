#pragma once

#include <Vector3f.h>

class Quaternion {
    private:
	double x;
	double y;
	double z;
	double w;

    public:
	Quaternion();
	Quaternion(double a, double b, double c, double d);

	void setX(double a) noexcept;
	void setY(double b) noexcept;
	void setZ(double c) noexcept;
	void setW(double d) noexcept;
	double getX() const noexcept;
	double getY() const noexcept;
	double getZ() const noexcept;
	double getW() const noexcept;

	double length() const noexcept;
	Quaternion normalize();
	Quaternion conjugate();

	Quaternion operator+(const Quaternion &v);
	Quaternion operator-(const Quaternion &v);
	Quaternion operator*(const Quaternion &v);
	Quaternion operator*(const Vector3f &v);
	Quaternion operator/(const Quaternion &v);
	Quaternion operator+(const double r);
	Quaternion operator-(const double r);
	Quaternion operator*(const double r);
	Quaternion operator/(const double r);

	Quaternion &operator+=(const Quaternion &v);
	Quaternion &operator-=(const Quaternion &v);
	Quaternion &operator*=(const Quaternion &v);
	Quaternion &operator*=(const Vector3f &v);
	Quaternion &operator/=(const Quaternion &v);
	Quaternion &operator+=(const double r);
	Quaternion &operator-=(const double r);
	Quaternion &operator*=(const double r);
	Quaternion &operator/=(const double r);
};
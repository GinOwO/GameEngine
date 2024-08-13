#pragma once

class Vector3f {
    private:
	double x;
	double y;
	double z;

    public:
	Vector3f();
	Vector3f(double a, double b, double c);

	void setX(double a) noexcept;
	void setY(double b) noexcept;
	void setZ(double c) noexcept;
	double getX() const noexcept;
	double getY() const noexcept;
	double getZ() const noexcept;

	double length() const noexcept;
	double dot(const Vector3f &v) noexcept;
	Vector3f normalize();

	Vector3f operator+(const Vector3f &v);
	Vector3f operator-(const Vector3f &v);
	Vector3f operator*(const Vector3f &v);
	Vector3f operator/(const Vector3f &v);
	Vector3f operator+(const double r);
	Vector3f operator-(const double r);
	Vector3f operator*(const double r);
	Vector3f operator/(const double r);

	Vector3f &operator+=(const Vector3f &v);
	Vector3f &operator-=(const Vector3f &v);
	Vector3f &operator*=(const Vector3f &v);
	Vector3f &operator/=(const Vector3f &v);
	Vector3f &operator+=(const double r);
	Vector3f &operator-=(const double r);
	Vector3f &operator*=(const double r);
	Vector3f &operator/=(const double r);

	Vector3f cross(const Vector3f &v) const noexcept;
};
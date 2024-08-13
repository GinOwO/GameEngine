#pragma once

class Vector2f {
    private:
	double x;
	double y;

    public:
	Vector2f();
	Vector2f(double a, double b);

	void setX(double a) noexcept;
	void setY(double b) noexcept;
	double getX() const noexcept;
	double getY() const noexcept;

	double length() const noexcept;
	double dot(const Vector2f &v) noexcept;
	Vector2f normalize();

	Vector2f operator+(const Vector2f &v);
	Vector2f operator-(const Vector2f &v);
	Vector2f operator*(const Vector2f &v);
	Vector2f operator/(const Vector2f &v);
	Vector2f operator+(const double r);
	Vector2f operator-(const double r);
	Vector2f operator*(const double r);
	Vector2f operator/(const double r);

	Vector2f &operator+=(const Vector2f &v);
	Vector2f &operator-=(const Vector2f &v);
	Vector2f &operator*=(const Vector2f &v);
	Vector2f &operator/=(const Vector2f &v);
	Vector2f &operator+=(const double r);
	Vector2f &operator-=(const double r);
	Vector2f &operator*=(const double r);
	Vector2f &operator/=(const double r);

	Vector2f rotate(double degrees) const noexcept;
};
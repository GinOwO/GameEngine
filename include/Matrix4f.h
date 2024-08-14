#pragma once

class Matrix4f {
    private:
	float matrix[4][4];

    public:
	Matrix4f();
	Matrix4f(const float m[4][4]);

	void set(int x, int y, float a) noexcept;
	float get(int x, int y) const noexcept;

	static Matrix4f Identity_Matrix();
	Matrix4f operator*(const Matrix4f &m) const noexcept;
	Matrix4f &operator*=(const Matrix4f &m) noexcept;
};
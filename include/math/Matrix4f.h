#pragma once

#include <math/Vector3f.h>

class Matrix4f {
    private:
	float matrix[4][4];

    public:
	Matrix4f();
	Matrix4f(const float m[4][4]);

	void set(int x, int y, float a) noexcept;
	float get(int x, int y) const noexcept;

	static Matrix4f Identity_Matrix();

	static Matrix4f Translation_Matrix(Vector3f vec);
	static Matrix4f Translation_Matrix(float x, float y, float z);

	static Matrix4f Rotation_Matrix(Vector3f vec);
	static Matrix4f Rotation_Matrix(float x, float y, float z);

	static Matrix4f Scale_Matrix(Vector3f vec);
	static Matrix4f Scale_Matrix(float x, float y, float z);

	static Matrix4f Projection_Matrix(float fov, float width, float height,
					  float zNear, float zFar);

	static Matrix4f flip_matrix(const Matrix4f &m);

	Matrix4f operator*(const Matrix4f &m) const noexcept;
	Matrix4f &operator*=(const Matrix4f &m) noexcept;

	const float *get_matrix() const noexcept;
};
#pragma once

#include <math/Vector3f.h>

class Matrix4f {
    private:
	float matrix[4][4];

    public:
	Matrix4f();
	Matrix4f(const float m[4][4]);

	void set(int x, int y, float a);
	float get(int x, int y) const;

	static Matrix4f Identity_Matrix();

	static Matrix4f Translation_Matrix(Vector3f vec);
	static Matrix4f Translation_Matrix(float x, float y, float z);

	static Matrix4f Rotation_Matrix(Vector3f vec);
	static Matrix4f Rotation_Matrix(float x, float y, float z);

	static Matrix4f Scale_Matrix(Vector3f vec);
	static Matrix4f Scale_Matrix(float x, float y, float z);

	static Matrix4f Perspective_Matrix(float fov, float aspect_ratio,
					   float zNear, float zFar);

	static Matrix4f Camera_Matrix(const Vector3f &forward,
				      const Vector3f &up);

	static Matrix4f Orthogonal_Matrix(float left, float right, float bottom,
					  float top, float near, float far);

	static Matrix4f flip_matrix(const Matrix4f &m);

	Matrix4f operator*(const Matrix4f &m) const noexcept;
	Matrix4f &operator*=(const Matrix4f &m) noexcept;

	bool operator==(const Matrix4f &m) const noexcept;

	const float *get_matrix() const noexcept;
};
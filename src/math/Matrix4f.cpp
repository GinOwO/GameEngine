#include <math/Matrix4f.h>

#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>

template <typename T> inline float to_degrees(T radians)
{
	return radians * (180.0 / M_PI);
}

template <typename T> inline float to_radians(T degrees)
{
	return (degrees * M_PI) / 180.0;
}

Matrix4f::Matrix4f()
{
	std::memset(matrix, 0, sizeof(matrix));
}

Matrix4f::Matrix4f(const float m[4][4])
{
	std::memcpy(matrix, m, sizeof(matrix));
}

Matrix4f Matrix4f::Identity_Matrix()
{
	float matrix[4][4] = { 0 };
	std::memset(matrix, 0, sizeof(matrix));
	matrix[0][0] = matrix[1][1] = matrix[2][2] = matrix[3][3] = 1;
	return { matrix };
}

Matrix4f Matrix4f::Translation_Matrix(Vector3f vec)
{
	return Matrix4f::Translation_Matrix(vec.getX(), vec.getY(), vec.getZ());
}

Matrix4f Matrix4f::Translation_Matrix(float x, float y, float z)
{
	float matrix[4][4] = { 0 };
	std::memset(matrix, 0, sizeof(matrix));
	matrix[0][0] = matrix[1][1] = matrix[2][2] = matrix[3][3] = 1;
	matrix[3][0] = x;
	matrix[3][1] = y;
	matrix[3][2] = z;
	return { matrix };
}

Matrix4f Matrix4f::Rotation_Matrix(Vector3f vec)
{
	return Matrix4f::Rotation_Matrix(vec.getX(), vec.getY(), vec.getZ());
}

Matrix4f Matrix4f::Rotation_Matrix(float x, float y, float z)
{
	Matrix4f rx = Matrix4f::Identity_Matrix();
	Matrix4f ry = Matrix4f::Identity_Matrix();
	Matrix4f rz = Matrix4f::Identity_Matrix();

	x = to_radians(x);
	y = to_radians(y);
	z = to_radians(z);

	rx.set(0, 0, cos(z)), rx.set(0, 1, -sin(z));
	rx.set(1, 0, sin(z)), rx.set(1, 1, cos(z));

	ry.set(1, 1, cos(x)), ry.set(1, 2, -sin(x));
	ry.set(2, 1, sin(x)), ry.set(2, 2, cos(x));

	rz.set(0, 0, cos(y)), rz.set(0, 0, -sin(y));
	rz.set(2, 0, sin(y)), rz.set(2, 0, cos(y));

	return rz * (ry * rx);
}

Matrix4f Matrix4f::Scale_Matrix(Vector3f vec)
{
	return Matrix4f::Scale_Matrix(vec.getX(), vec.getY(), vec.getZ());
}

Matrix4f Matrix4f::Scale_Matrix(float x, float y, float z)
{
	float matrix[4][4] = { 0 };
	std::memset(matrix, 0, sizeof(matrix));
	matrix[0][0] = x;
	matrix[1][1] = y;
	matrix[2][2] = z;
	matrix[3][3] = 1;
	return { matrix };
}

void Matrix4f::set(int x, int y, float a) noexcept
{
	if (x > 3 || y > 3 || x < 0 || y < 0) {
		std::cerr << "Setting out of bounds, exiting\n";
		exit(EXIT_FAILURE);
	}
	matrix[x][y] = a;
}

float Matrix4f::get(int x, int y) const noexcept
{
	if (x > 3 || y > 3 || x < 0 || y < 0) {
		std::cerr << "Getting out of bounds, exiting\n";
		exit(EXIT_FAILURE);
	}
	return matrix[x][y];
}

Matrix4f Matrix4f::operator*(const Matrix4f &m) const noexcept
{
	Matrix4f resultant(matrix);
	return resultant *= m;
}

Matrix4f &Matrix4f::operator*=(const Matrix4f &m) noexcept
{
	float tmp[4][4] = { 0 };
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				tmp[i][j] += matrix[i][k] * m.matrix[k][j];
			}
		}
	}
	std::memcpy(matrix, tmp, sizeof(tmp));
	return *this;
}

const float *Matrix4f::get_matrix() const noexcept
{
	return &matrix[0][0];
}
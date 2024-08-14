#include <math/Matrix4f.h>

#include <cstdlib>
#include <cstring>
#include <iostream>

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
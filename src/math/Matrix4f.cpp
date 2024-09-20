#include <math/Matrix4f.h>

#include <math/Vector3f.h>

#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <exception>
#include <exception>

template <typename T> inline float to_degrees(T radians)
{
	return radians * (180.0 / M_PI);
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
	matrix[0][0] = matrix[1][1] = matrix[2][2] = matrix[3][3] = 1;
	matrix[0][3] = x;
	matrix[1][3] = y;
	matrix[2][3] = z;
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

	rx.set(0, 0, std::cos(z)), rx.set(0, 1, -std::sin(z));
	rx.set(1, 0, std::sin(z)), rx.set(1, 1, std::cos(z));

	ry.set(1, 1, std::cos(x)), ry.set(1, 2, -std::sin(x));
	ry.set(2, 1, std::sin(x)), ry.set(2, 2, std::cos(x));

	rz.set(0, 0, std::cos(y)), rz.set(0, 2, -std::sin(y));
	rz.set(2, 0, std::sin(y)), rz.set(2, 2, std::cos(y));

	return rz * (ry * rx);
}

Matrix4f Matrix4f::Scale_Matrix(Vector3f vec)
{
	return Matrix4f::Scale_Matrix(vec.getX(), vec.getY(), vec.getZ());
}

Matrix4f Matrix4f::Scale_Matrix(float x, float y, float z)
{
	float matrix[4][4] = { 0 };
	matrix[0][0] = x;
	matrix[1][1] = y;
	matrix[2][2] = z;
	matrix[3][3] = 1;
	return { matrix };
}

Matrix4f Matrix4f::Perspective_Matrix(float fov, float aspect_ratio,
				      float zNear, float zFar)
{
	float tan_half_fov = std::tan(fov / 2.0f);
	float zRange = zNear - zFar;

	float matrix[4][4] = { 0.0f };
	matrix[0][0] = 1.0f / (tan_half_fov * aspect_ratio);
	matrix[1][1] = 1.0f / tan_half_fov;
	matrix[2][2] = (-zNear - zFar) / zRange;
	matrix[2][3] = (2.0f * zFar * zNear) / zRange;
	matrix[3][2] = 1.0f;

	return { matrix };
}

Matrix4f Matrix4f::Camera_Matrix(const Vector3f &forward, const Vector3f &up)
{
	Vector3f f = forward.normalize();
	Vector3f r = up.normalize();

	r = r.cross(f);
	Vector3f u{ f.cross(r) };

	float matrix[4][4] = { 0 };

	matrix[0][0] = r.getX();
	matrix[0][1] = r.getY();
	matrix[0][2] = r.getZ();

	matrix[1][0] = u.getX();
	matrix[1][1] = u.getY();
	matrix[1][2] = u.getZ();

	matrix[2][0] = f.getX();
	matrix[2][1] = f.getY();
	matrix[2][2] = f.getZ();

	matrix[3][3] = 1;
	return { matrix };
}

void Matrix4f::set(int x, int y, float a)
{
	if (x > 3 || y > 3 || x < 0 || y < 0) {
		std::cerr << "Matrix setting out of bounds, exiting\n";
		throw std::invalid_argument(
			"Matrix setting out of bounds, exiting\n");
		std::cerr << "Matrix setting out of bounds, exiting\n";
		throw std::invalid_argument(
			"Matrix setting out of bounds, exiting\n");
	}
	matrix[x][y] = a;
}

float Matrix4f::get(int x, int y) const
{
	if (x > 3 || y > 3 || x < 0 || y < 0) {
		std::cerr << "Matrix getting out of bounds, exiting\n";
		throw std::invalid_argument(
			"Matrix getting out of bounds, exiting\n");
		std::cerr << "Matrix getting out of bounds, exiting\n";
		throw std::invalid_argument(
			"Matrix getting out of bounds, exiting\n");
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

Matrix4f Matrix4f::flip_matrix(const Matrix4f &m)
{
	float tmp[4][4];
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			tmp[i][j] = m.get(j, i);
		}
	}
	return Matrix4f(tmp);
}

const float *Matrix4f::get_matrix() const noexcept
{
	return &matrix[0][0];
}

Matrix4f Matrix4f::Orthogonal_Matrix(float left, float right, float bottom,
				     float top, float near, float far)
{
	float matrix[4][4];

	float width = right - left;
	float height = top - bottom;
	float depth = far - near;

	matrix[3][3] = 1.0f;

	// Scaling
	matrix[0][0] = 2.0f / width;
	matrix[1][1] = 2.0f / height;
	matrix[2][2] = -2.0f / depth;

	// Translating
	matrix[0][3] = -(right + left) / width;
	matrix[1][3] = -(top + bottom) / height;
	matrix[2][3] = -(far + near) / depth;

	return { matrix };
}

Matrix4f Matrix4f::Rotation_Matrix(const Vector3f &f, const Vector3f &u,
				   const Vector3f &r)
{
	float matrix[4][4] = { 0 };

	matrix[0][0] = r.getX();
	matrix[0][1] = r.getY();
	matrix[0][2] = r.getZ();
	matrix[0][3] = 0;
	matrix[1][0] = u.getX();
	matrix[1][1] = u.getY();
	matrix[1][2] = u.getZ();
	matrix[1][3] = 0;
	matrix[2][0] = f.getX();
	matrix[2][1] = f.getY();
	matrix[2][2] = f.getZ();
	matrix[2][3] = 0;
	matrix[3][0] = 0;
	matrix[3][1] = 0;
	matrix[3][2] = 0;
	matrix[3][3] = 1;

	return Matrix4f{ matrix };
}

Matrix4f Matrix4f::Rotation_Matrix(const Vector3f &forward, const Vector3f &up)
{
	Vector3f f = forward.normalize();

	Vector3f r = up.normalize();
	r = r.cross(f);

	Vector3f u = f.cross(r);

	return Rotation_Matrix(f, u, r);
}

Vector3f Matrix4f::transform(const Vector3f &r)
{
	return { matrix[0][0] * r.getX() + matrix[0][1] * r.getY() +
			 matrix[0][2] * r.getZ() + matrix[0][3],
		 matrix[1][0] * r.getX() + matrix[1][1] * r.getY() +
			 matrix[1][2] * r.getZ() + matrix[1][3],
		 matrix[2][0] * r.getX() + matrix[2][1] * r.getY() +
			 matrix[2][2] * r.getZ() + matrix[2][3] };
}
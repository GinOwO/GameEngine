#include <math/Matrix4f.h>

#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <exception>

template <typename T> inline float to_degrees(T radians)
{
	return radians * (180.0 / M_PI);
}

template <typename T> inline float to_radians(T degrees)
{
	return (degrees * M_PI) / 180.0;
}

/***************************************************************************
 * @brief Default constructor for Matrix4f.
 *
 * Initializes a 4x4 matrix with all elements set to 0.
 ***************************************************************************/
Matrix4f::Matrix4f()
{
	std::memset(matrix, 0, sizeof(matrix));
}

/***************************************************************************
 * @brief Constructs a Matrix4f with a given 4x4 matrix.
 *
 * Initializes the matrix with the provided 4x4 array.
 *
 * @param m A 4x4 array of floats to initialize the matrix.
 ***************************************************************************/
Matrix4f::Matrix4f(const float m[4][4])
{
	std::memcpy(matrix, m, sizeof(matrix));
}

/***************************************************************************
 * @brief Creates an identity matrix.
 *
 * Returns a 4x4 identity matrix.
 *
 * @return A Matrix4f object representing the identity matrix.
 ***************************************************************************/
Matrix4f Matrix4f::Identity_Matrix()
{
	float matrix[4][4] = { 0 };
	matrix[0][0] = matrix[1][1] = matrix[2][2] = matrix[3][3] = 1;
	return { matrix };
}

/***************************************************************************
 * @brief Creates a translation matrix from a Vector3f.
 *
 * Returns a 4x4 translation matrix based on the provided vector.
 *
 * @param vec The vector specifying translation along x, y, and z axes.
 * @return A Matrix4f object representing the translation matrix.
 ***************************************************************************/
Matrix4f Matrix4f::Translation_Matrix(Vector3f vec)
{
	return Matrix4f::Translation_Matrix(vec.getX(), vec.getY(), vec.getZ());
}

/***************************************************************************
 * @brief Creates a translation matrix from x, y, and z values.
 *
 * Returns a 4x4 translation matrix with translation applied to the x, y, and z axes.
 *
 * @param x The translation along the x-axis.
 * @param y The translation along the y-axis.
 * @param z The translation along the z-axis.
 * @return A Matrix4f object representing the translation matrix.
 ***************************************************************************/
Matrix4f Matrix4f::Translation_Matrix(float x, float y, float z)
{
	float matrix[4][4] = { 0 };
	matrix[0][0] = matrix[1][1] = matrix[2][2] = matrix[3][3] = 1;
	matrix[0][3] = x;
	matrix[1][3] = y;
	matrix[2][3] = z;
	return { matrix };
}

/***************************************************************************
 * @brief Creates a rotation matrix from a Vector3f.
 *
 * Returns a 4x4 rotation matrix based on the provided vector.
 *
 * @param vec The vector specifying rotation angles around the x, y, and z axes.
 * @return A Matrix4f object representing the rotation matrix.
 ***************************************************************************/
Matrix4f Matrix4f::Rotation_Matrix(Vector3f vec)
{
	return Matrix4f::Rotation_Matrix(vec.getX(), vec.getY(), vec.getZ());
}

/***************************************************************************
 * @brief Creates a rotation matrix from x, y, and z angles.
 *
 * Returns a 4x4 rotation matrix with rotation applied around the x, y, and z axes.
 *
 * @param x The rotation angle around the x-axis in degrees.
 * @param y The rotation angle around the y-axis in degrees.
 * @param z The rotation angle around the z-axis in degrees.
 * @return A Matrix4f object representing the rotation matrix.
 ***************************************************************************/
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

/***************************************************************************
 * @brief Creates a scaling matrix from a Vector3f.
 *
 * Returns a 4x4 scaling matrix based on the provided vector.
 *
 * @param vec The vector specifying scaling factors along x, y, and z axes.
 * @return A Matrix4f object representing the scaling matrix.
 ***************************************************************************/
Matrix4f Matrix4f::Scale_Matrix(Vector3f vec)
{
	return Matrix4f::Scale_Matrix(vec.getX(), vec.getY(), vec.getZ());
}

/***************************************************************************
 * @brief Creates a scaling matrix from x, y, and z values.
 *
 * Returns a 4x4 scaling matrix with scaling applied to the x, y, and z axes.
 *
 * @param x The scaling factor along the x-axis.
 * @param y The scaling factor along the y-axis.
 * @param z The scaling factor along the z-axis.
 * @return A Matrix4f object representing the scaling matrix.
 ***************************************************************************/
Matrix4f Matrix4f::Scale_Matrix(float x, float y, float z)
{
	float matrix[4][4] = { 0 };
	matrix[0][0] = x;
	matrix[1][1] = y;
	matrix[2][2] = z;
	matrix[3][3] = 1;
	return { matrix };
}

/***************************************************************************
 * @brief Creates a perspective projection matrix.
 *
 * Returns a 4x4 matrix for perspective projection with specified field of view, 
 * aspect ratio, and near and far clipping planes.
 *
 * @param fov The field of view in degrees.
 * @param aspect_ratio The aspect ratio of the viewport.
 * @param zNear The distance to the near clipping plane.
 * @param zFar The distance to the far clipping plane.
 * @return A Matrix4f object representing the perspective projection matrix.
 ***************************************************************************/
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

/***************************************************************************
 * @brief Creates a camera matrix for view transformation.
 *
 * Returns a 4x4 camera matrix based on the provided forward and up vectors.
 *
 * @param forward The forward direction vector of the camera.
 * @param up The up direction vector of the camera.
 * @return A Matrix4f object representing the camera matrix.
 ***************************************************************************/
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

/***************************************************************************
 * @brief Sets a specific element in the matrix.
 *
 * Updates the value at position (x, y) in the matrix.
 *
 * @param x The row index.
 * @param y The column index.
 * @param a The value to set at (x, y).
 * @throws std::invalid_argument if (x, y) is out of bounds.
 ***************************************************************************/
void Matrix4f::set(int x, int y, float a)
{
	if (x > 3 || y > 3 || x < 0 || y < 0) {
		std::cerr << "Matrix setting out of bounds, exiting\n";
		throw std::invalid_argument(
			"Matrix setting out of bounds, exiting\n");
	}
	matrix[x][y] = a;
}

/***************************************************************************
 * @brief Gets the value at a specific position in the matrix.
 *
 * Retrieves the value at position (x, y) in the matrix.
 *
 * @param x The row index.
 * @param y The column index.
 * @return The value at (x, y).
 * @throws std::invalid_argument if (x, y) is out of bounds.
 ***************************************************************************/
float Matrix4f::get(int x, int y) const
{
	if (x > 3 || y > 3 || x < 0 || y < 0) {
		std::cerr << "Matrix getting out of bounds, exiting\n";
		throw std::invalid_argument(
			"Matrix getting out of bounds, exiting\n");
	}
	return matrix[x][y];
}

/***************************************************************************
 * @brief Multiplies two matrices.
 *
 * Multiplies the current matrix by another matrix and returns the result.
 *
 * @param m The matrix to multiply with.
 * @return The resulting matrix after multiplication.
 ***************************************************************************/
Matrix4f Matrix4f::operator*(const Matrix4f &m) const noexcept
{
	Matrix4f resultant(matrix);
	return resultant *= m;
}

/***************************************************************************
 * @brief Multiplies the current matrix by another matrix.
 *
 * Updates the current matrix with the result of the multiplication.
 *
 * @param m The matrix to multiply with.
 * @return A reference to the updated matrix.
 ***************************************************************************/
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

/***************************************************************************
 * @brief Flips the given matrix (transpose).
 *
 * Returns the transposed matrix of the given matrix.
 *
 * @param m The matrix to transpose.
 * @return The transposed matrix.
 ***************************************************************************/
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

/***************************************************************************
 * @brief Gets a pointer to the matrix data.
 *
 * Retrieves a pointer to the internal matrix data.
 *
 * @return A pointer to the matrix data.
 ***************************************************************************/
const float *Matrix4f::get_matrix() const noexcept
{
	return &matrix[0][0];
}

/***************************************************************************
 * @brief Compares two matrices for equality.
 *
 * Checks if the current matrix is equal to another matrix.
 *
 * @param m The matrix to compare with.
 * @return True if the matrices are equal, false otherwise.
 ***************************************************************************/
bool Matrix4f::operator==(const Matrix4f &m) const noexcept
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (this->matrix[i][j] != m.matrix[i][j])
				return false;
		}
	}
	return true;
}

/***************************************************************************
 * @brief Creates an orthogonal projection matrix.
 *
 * Returns a 4x4 matrix for orthogonal projection with specified bounds.
 *
 * @param left The left bound of the view volume.
 * @param right The right bound of the view volume.
 * @param bottom The bottom bound of the view volume.
 * @param top The top bound of the view volume.
 * @param near The near clipping plane distance.
 * @param far The far clipping plane distance.
 * @return A Matrix4f object representing the orthogonal projection matrix.
 ***************************************************************************/
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

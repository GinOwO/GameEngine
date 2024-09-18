/***************************************************************************
 * @file Matrix4f.h
 *
 * @brief Declares the Matrix4f class for 4x4 matrices.
 *
 * This file contains the declaration of the Matrix4f class, which represents
 * a 4x4 matrix and provides various static methods to create transformation
 * matrices, such as translation, rotation, and scaling. It also includes
 * methods for matrix operations like multiplication and comparison.
 *
 ***************************************************************************/

#pragma once

#include <math/Vector3f.h>

/***************************************************************************
 * @class Matrix4f
 *
 * @brief Represents a 4x4 matrix for transformations and operations.
 *
 * The Matrix4f class encapsulates a 4x4 matrix and provides static methods
 * to create common transformation matrices. It supports matrix multiplication,
 * comparison, and retrieval of matrix data.
 *
 ***************************************************************************/
class Matrix4f {
    private:
	float matrix[4][4]; /**< The 4x4 matrix data. */

    public:
	/***************************************************************************
	 * @brief Default constructor for the Matrix4f class.
	 *
	 * Initializes the matrix to the identity matrix.
	 ***************************************************************************/
	Matrix4f();

	/***************************************************************************
	 * @brief Constructs a Matrix4f with a given 4x4 array.
	 *
	 * @param m The 4x4 array to initialize the matrix with.
	 ***************************************************************************/
	Matrix4f(const float m[4][4]);

	/***************************************************************************
	 * @brief Sets a value in the matrix.
	 *
	 * @param x The row index.
	 * @param y The column index.
	 * @param a The value to set.
	 ***************************************************************************/
	void set(int x, int y, float a);

	/***************************************************************************
	 * @brief Gets a value from the matrix.
	 *
	 * @param x The row index.
	 * @param y The column index.
	 * @return The value at the specified index.
	 ***************************************************************************/
	float get(int x, int y) const;

	/***************************************************************************
	 * @brief Creates an identity matrix.
	 *
	 * @return The identity matrix.
	 ***************************************************************************/
	static Matrix4f Identity_Matrix();

	/***************************************************************************
	 * @brief Creates a translation matrix from a Vector3f.
	 *
	 * @param vec The translation vector.
	 * @return The translation matrix.
	 ***************************************************************************/
	static Matrix4f Translation_Matrix(Vector3f vec);

	/***************************************************************************
	 * @brief Creates a translation matrix from x, y, and z values.
	 *
	 * @param x The translation along the x-axis.
	 * @param y The translation along the y-axis.
	 * @param z The translation along the z-axis.
	 * @return The translation matrix.
	 ***************************************************************************/
	static Matrix4f Translation_Matrix(float x, float y, float z);

	/***************************************************************************
	 * @brief Creates a rotation matrix from a Vector3f.
	 *
	 * @param vec The rotation vector (angle in radians).
	 * @return The rotation matrix.
	 ***************************************************************************/
	static Matrix4f Rotation_Matrix(Vector3f vec);

	/***************************************************************************
	 * @brief Creates a rotation matrix from x, y, and z values.
	 *
	 * @param x The rotation around the x-axis (angle in radians).
	 * @param y The rotation around the y-axis (angle in radians).
	 * @param z The rotation around the z-axis (angle in radians).
	 * @return The rotation matrix.
	 ***************************************************************************/
	static Matrix4f Rotation_Matrix(float x, float y, float z);

	/***************************************************************************
	 * @brief Creates a scaling matrix from a Vector3f.
	 *
	 * @param vec The scaling vector.
	 * @return The scaling matrix.
	 ***************************************************************************/
	static Matrix4f Scale_Matrix(Vector3f vec);

	/***************************************************************************
	 * @brief Creates a scaling matrix from x, y, and z values.
	 *
	 * @param x The scaling factor along the x-axis.
	 * @param y The scaling factor along the y-axis.
	 * @param z The scaling factor along the z-axis.
	 * @return The scaling matrix.
	 ***************************************************************************/
	static Matrix4f Scale_Matrix(float x, float y, float z);

	/***************************************************************************
	 * @brief Creates a perspective projection matrix.
	 *
	 * @param fov The field of view (in radians).
	 * @param aspect_ratio The aspect ratio of the view.
	 * @param zNear The near clipping plane.
	 * @param zFar The far clipping plane.
	 * @return The perspective projection matrix.
	 ***************************************************************************/
	static Matrix4f Perspective_Matrix(float fov, float aspect_ratio,
					   float zNear, float zFar);

	/***************************************************************************
	 * @brief Creates a camera matrix for view transformations.
	 *
	 * @param forward The forward direction of the camera.
	 * @param up The up direction of the camera.
	 * @return The camera matrix.
	 ***************************************************************************/
	static Matrix4f Camera_Matrix(const Vector3f &forward,
				      const Vector3f &up);

	/***************************************************************************
	 * @brief Creates an orthogonal projection matrix.
	 *
	 * @param left The left clipping plane.
	 * @param right The right clipping plane.
	 * @param bottom The bottom clipping plane.
	 * @param top The top clipping plane.
	 * @param near The near clipping plane.
	 * @param far The far clipping plane.
	 * @return The orthogonal projection matrix.
	 ***************************************************************************/
	static Matrix4f Orthogonal_Matrix(float left, float right, float bottom,
					  float top, float near, float far);

	/***************************************************************************
	 * @brief Flips a matrix along its diagonal.
	 *
	 * @param m The matrix to flip.
	 * @return The flipped matrix.
	 ***************************************************************************/
	static Matrix4f flip_matrix(const Matrix4f &m);

	/***************************************************************************
	 * @brief Multiplies the matrix with another matrix.
	 *
	 * @param m The matrix to multiply with.
	 * @return The resulting matrix after multiplication.
	 ***************************************************************************/
	Matrix4f operator*(const Matrix4f &m) const noexcept;

	/***************************************************************************
	 * @brief Multiplies the matrix by another matrix (in-place).
	 *
	 * @param m The matrix to multiply with.
	 * @return A reference to this matrix after multiplication.
	 ***************************************************************************/
	Matrix4f &operator*=(const Matrix4f &m) noexcept;

	/***************************************************************************
	 * @brief Checks if the matrix is equal to another matrix.
	 *
	 * @param m The matrix to compare with.
	 * @return True if the matrices are equal, false otherwise.
	 ***************************************************************************/
	constexpr bool operator==(const Matrix4f &m) const noexcept
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
	 * @brief Gets a pointer to the matrix data.
	 *
	 * @return A pointer to the matrix data.
	 ***************************************************************************/
	const float *get_matrix() const noexcept;

	//TODO: comment
	static Matrix4f Rotation_Matrix(const Vector3f &forward,
					const Vector3f &up,
					const Vector3f &right);

	Vector3f transform(const Vector3f &r);
};

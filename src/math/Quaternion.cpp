#include <math/Quaternion.h>

#include <math/Vector3f.h>
#include <math/Matrix4f.h>

#include <cmath>

/***************************************************************************
 * @brief Default constructor for Quaternion.
 *
 * Initializes a quaternion with all components set to 0.
 ***************************************************************************/
Quaternion::Quaternion()
{
	x = y = z = w = 0;
}

/***************************************************************************
 * @brief Constructs a Quaternion with specified components.
 *
 * Initializes a quaternion with the given values for x, y, z, and w.
 *
 * @param a The x component of the quaternion.
 * @param b The y component of the quaternion.
 * @param c The z component of the quaternion.
 * @param d The w component of the quaternion.
 ***************************************************************************/
Quaternion::Quaternion(float a, float b, float c, float d)
{
	x = a;
	y = b;
	z = c;
	w = d;
}

/***************************************************************************
 * @brief Sets the x component of the quaternion.
 *
 * @param a The new value for the x component.
 ***************************************************************************/
void Quaternion::setX(float a) noexcept
{
	this->x = a;
}

/***************************************************************************
 * @brief Sets the y component of the quaternion.
 *
 * @param b The new value for the y component.
 ***************************************************************************/
void Quaternion::setY(float b) noexcept
{
	this->y = b;
}

/***************************************************************************
 * @brief Sets the z component of the quaternion.
 *
 * @param c The new value for the z component.
 ***************************************************************************/
void Quaternion::setZ(float c) noexcept
{
	this->z = c;
}

/***************************************************************************
 * @brief Sets the w component of the quaternion.
 *
 * @param d The new value for the w component.
 ***************************************************************************/
void Quaternion::setW(float d) noexcept
{
	this->w = d;
}

/***************************************************************************
 * @brief Gets the x component of the quaternion.
 *
 * @return The x component of the quaternion.
 ***************************************************************************/
float Quaternion::getX() const noexcept
{
	return this->x;
}

/***************************************************************************
 * @brief Gets the y component of the quaternion.
 *
 * @return The y component of the quaternion.
 ***************************************************************************/
float Quaternion::getY() const noexcept
{
	return this->y;
}

/***************************************************************************
 * @brief Gets the z component of the quaternion.
 *
 * @return The z component of the quaternion.
 ***************************************************************************/
float Quaternion::getZ() const noexcept
{
	return this->z;
}

/***************************************************************************
 * @brief Gets the w component of the quaternion.
 *
 * @return The w component of the quaternion.
 ***************************************************************************/
float Quaternion::getW() const noexcept
{
	return this->w;
}

/***************************************************************************
 * @brief Computes the length of the quaternion.
 *
 * @return The length (magnitude) of the quaternion.
 ***************************************************************************/
float Quaternion::length() const noexcept
{
	return std::sqrt(x * x + y * y + z * z + w * w);
}

/***************************************************************************
 * @brief Normalizes the quaternion.
 *
 * Returns a normalized quaternion (unit length).
 *
 * @return The normalized quaternion.
 ***************************************************************************/
Quaternion Quaternion::normalize() const noexcept
{
	float len = length();
	if (len == 0)
		len = 1;
	return { x / len, y / len, z / len, w / len };
}

/***************************************************************************
 * @brief Computes the conjugate of the quaternion.
 *
 * Returns the conjugate of the quaternion (negate x, y, z).
 *
 * @return The conjugate of the quaternion.
 ***************************************************************************/
Quaternion Quaternion::conjugate() const noexcept
{
	return { -x, -y, -z, w };
}

/***************************************************************************
 * @brief Adds two quaternions.
 *
 * @param v The quaternion to add.
 * @return The resulting quaternion after addition.
 ***************************************************************************/
Quaternion Quaternion::operator+(const Quaternion &v) const noexcept
{
	return { x + v.x, y + v.y, z + v.z, w + v.w };
}

/***************************************************************************
 * @brief Subtracts a quaternion from the current quaternion.
 *
 * @param v The quaternion to subtract.
 * @return The resulting quaternion after subtraction.
 ***************************************************************************/
Quaternion Quaternion::operator-(const Quaternion &v) const noexcept
{
	return { x - v.x, y - v.y, z - v.z, w - v.w };
}

/***************************************************************************
 * @brief Multiplies two quaternions.
 *
 * @param v The quaternion to multiply with.
 * @return The resulting quaternion after multiplication.
 ***************************************************************************/
Quaternion Quaternion::operator*(const Quaternion &v) const noexcept
{
	return { w * v.x + x * v.w + y * v.z - z * v.y,
		 w * v.y - x * v.z + y * v.w + z * v.x,
		 w * v.z + x * v.y - y * v.x + z * v.w,
		 w * v.w - x * v.x - y * v.y - z * v.z };
}

/***************************************************************************
 * @brief Multiplies the quaternion with a Vector3f.
 *
 * @param v The vector to multiply with.
 * @return The resulting quaternion after multiplication.
 ***************************************************************************/
Quaternion Quaternion::operator*(const Vector3f &v) const noexcept
{
	return { w * v.getX() + y * v.getZ() - z * v.getY(),
		 w * v.getY() + z * v.getX() - x * v.getZ(),
		 w * v.getZ() + x * v.getY() - y * v.getX(),
		 -x * v.getX() - y * v.getY() - z * v.getZ() };
}

/***************************************************************************
 * @brief Divides the quaternion by another quaternion.
 *
 * @param v The quaternion to divide by.
 * @return The resulting quaternion after division.
 ***************************************************************************/
Quaternion Quaternion::operator/(const Quaternion &v) const noexcept
{
	return { x / v.x, y / v.y, z / v.z, w / v.w };
}

/***************************************************************************
 * @brief Adds a scalar value to the quaternion.
 *
 * @param r The scalar value to add.
 * @return The resulting quaternion after addition.
 ***************************************************************************/
Quaternion Quaternion::operator+(const float r) const noexcept
{
	return { x + r, y + r, z + r, w + r };
}

/***************************************************************************
 * @brief Subtracts a scalar value from the quaternion.
 *
 * @param r The scalar value to subtract.
 * @return The resulting quaternion after subtraction.
 ***************************************************************************/
Quaternion Quaternion::operator-(const float r) const noexcept
{
	return { x - r, y - r, z - r, w - r };
}

/***************************************************************************
 * @brief Multiplies the quaternion by a scalar value.
 *
 * @param r The scalar value to multiply with.
 * @return The resulting quaternion after multiplication.
 ***************************************************************************/
Quaternion Quaternion::operator*(const float r) const noexcept
{
	return { x * r, y * r, z * r, w * r };
}

/***************************************************************************
 * @brief Divides the quaternion by a scalar value.
 *
 * @param r The scalar value to divide by.
 * @return The resulting quaternion after division.
 ***************************************************************************/
Quaternion Quaternion::operator/(const float r) const noexcept
{
	return { x / r, y / r, z / r, w / r };
}

/***************************************************************************
 * @brief Adds another quaternion to the current quaternion.
 *
 * Updates the current quaternion with the result of the addition.
 *
 * @param v The quaternion to add.
 * @return A reference to the updated quaternion.
 ***************************************************************************/
Quaternion &Quaternion::operator+=(const Quaternion &v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	w += v.w;
	return *this;
}

/***************************************************************************
 * @brief Subtracts another quaternion from the current quaternion.
 *
 * Updates the current quaternion with the result of the subtraction.
 *
 * @param v The quaternion to subtract.
 * @return A reference to the updated quaternion.
 ***************************************************************************/
Quaternion &Quaternion::operator-=(const Quaternion &v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	w -= v.w;
	return *this;
}

/***************************************************************************
 * @brief Multiplies the current quaternion by another quaternion.
 *
 * Updates the current quaternion with the result of the multiplication.
 *
 * @param v The quaternion to multiply with.
 * @return A reference to the updated quaternion.
 ***************************************************************************/
Quaternion &Quaternion::operator*=(const Quaternion &v)
{
	float a = x * v.y + w * v.x + y * v.z - z * v.y,
	      b = y * v.w + w * v.y + z * v.x - x * v.z,
	      c = w * v.w + w * v.z + x * v.y - y * v.x,
	      d = w * v.w - x * v.x - y * v.y - z * v.z;
	x = a;
	y = b;
	z = c;
	w = d;
	return *this;
}

/***************************************************************************
 * @brief Multiplies the current quaternion by a Vector3f.
 *
 * Updates the current quaternion with the result of the multiplication.
 *
 * @param v The vector to multiply with.
 * @return A reference to the updated quaternion.
 ***************************************************************************/
Quaternion &Quaternion::operator*=(const Vector3f &v)
{
	float a = w * v.getX() + y * v.getZ() - z * v.getY(),
	      b = w * v.getY() + z * v.getX() - x * v.getZ(),
	      c = w * v.getZ() + x * v.getY() - y * v.getX(),
	      d = -x * v.getX() - y * v.getY() - z * v.getZ();

	x = a;
	y = b;
	z = c;
	w = d;
	return *this;
}

/***************************************************************************
 * @brief Divides the current quaternion by another quaternion.
 *
 * Updates the current quaternion with the result of the division.
 *
 * @param v The quaternion to divide by.
 * @return A reference to the updated quaternion.
 ***************************************************************************/
Quaternion &Quaternion::operator/=(const Quaternion &v)
{
	x /= v.x;
	y /= v.y;
	z /= v.z;
	w /= v.w;
	return *this;
}

/***************************************************************************
 * @brief Adds a scalar value to the current quaternion.
 *
 * Updates the current quaternion with the result of the addition.
 *
 * @param r The scalar value to add.
 * @return A reference to the updated quaternion.
 ***************************************************************************/
Quaternion &Quaternion::operator+=(const float r)
{
	x += r;
	y += r;
	z += r;
	w += r;
	return *this;
}

/***************************************************************************
 * @brief Subtracts a scalar value from the current quaternion.
 *
 * Updates the current quaternion with the result of the subtraction.
 *
 * @param r The scalar value to subtract.
 * @return A reference to the updated quaternion.
 ***************************************************************************/
Quaternion &Quaternion::operator-=(const float r)
{
	x -= r;
	y -= r;
	z -= r;
	w -= r;
	return *this;
}

/***************************************************************************
 * @brief Multiplies the current quaternion by a scalar value.
 *
 * Updates the current quaternion with the result of the multiplication.
 *
 * @param r The scalar value to multiply with.
 * @return A reference to the updated quaternion.
 ***************************************************************************/
Quaternion &Quaternion::operator*=(const float r)
{
	x *= r;
	y *= r;
	z *= r;
	w *= r;
	return *this;
}

/***************************************************************************
 * @brief Divides the current quaternion by a scalar value.
 *
 * Updates the current quaternion with the result of the division.
 *
 * @param r The scalar value to divide by.
 * @return A reference to the updated quaternion.
 ***************************************************************************/
Quaternion &Quaternion::operator/=(const float r)
{
	x /= r;
	y /= r;
	z /= r;
	w /= r;
	return *this;
}

/***************************************************************************
 * @brief Returns the forward direction based on the quaternion.
 *
 * @return A Vector3f representing the forward direction.
 ***************************************************************************/
Vector3f Quaternion::get_forward() const
{
	return Vector3f{ 0, 0, 1 }.rotate(this->get());
}

/***************************************************************************
 * @brief Returns the backward direction based on the quaternion.
 *
 * @return A Vector3f representing the backward direction.
 ***************************************************************************/
Vector3f Quaternion::get_backward() const
{
	return Vector3f{ 0, 0, -1 }.rotate(this->get());
}

/***************************************************************************
 * @brief Returns the upward direction based on the quaternion.
 *
 * @return A Vector3f representing the upward direction.
 ***************************************************************************/
Vector3f Quaternion::get_up() const
{
	return Vector3f{ 0, -1, 0 }.rotate(this->get());
}

/***************************************************************************
 * @brief Returns the downward direction based on the quaternion.
 *
 * @return A Vector3f representing the downward direction.
 ***************************************************************************/
Vector3f Quaternion::get_down() const
{
	return Vector3f{ 0, -1, 0 }.rotate(this->get());
}

/***************************************************************************
 * @brief Returns the right direction based on the quaternion.
 *
 * @return A Vector3f representing the right direction.
 ***************************************************************************/
Vector3f Quaternion::get_right() const
{
	return Vector3f{ 1, 0, 0 }.rotate(this->get());
}

/***************************************************************************
 * @brief Returns the left direction based on the quaternion.
 *
 * @return A Vector3f representing the left direction.
 ***************************************************************************/
Vector3f Quaternion::get_left() const
{
	return Vector3f{ -1, 0, 0 }.rotate(this->get());
}

// TODO: Comment
Matrix4f Quaternion::to_rotation_matrix() const noexcept
{
	Vector3f forward = Vector3f(2.0f * (x * z - w * y),
				    2.0f * (y * z + w * x),
				    1.0f - 2.0f * (x * x + y * y));
	Vector3f up = Vector3f(2.0f * (x * y + w * z),
			       1.0f - 2.0f * (x * x + z * z),
			       2.0f * (y * z - w * x));
	Vector3f right = Vector3f(1.0f - 2.0f * (y * y + z * z),
				  2.0f * (x * y - w * z),
				  2.0f * (x * z + w * y));

	return Matrix4f::Rotation_Matrix(forward, up, right);
}

Quaternion Quaternion::Rotation_Quaternion(const Vector3f &axis,
					   float angle) noexcept
{
	float x, y, z, w;
	float sinHalfAngle = (float)std::sin(angle / 2);
	float cosHalfAngle = (float)std::cos(angle / 2);

	x = axis.getX() * sinHalfAngle;
	y = axis.getY() * sinHalfAngle;
	z = axis.getZ() * sinHalfAngle;
	w = cosHalfAngle;

	return { x, y, z, w };
}

std::array<float, 4> Quaternion::get() const noexcept
{
	return { x, y, z, w };
}
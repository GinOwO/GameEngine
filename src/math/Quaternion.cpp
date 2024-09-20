#include <math/Quaternion.h>

#include <math/Vector3f.h>
#include <math/Matrix4f.h>

#include <cmath>

Quaternion::Quaternion()
{
	x = y = z = w = 0;
}

Quaternion::Quaternion(float a, float b, float c, float d)
{
	x = a;
	y = b;
	z = c;
	w = d;
}

void Quaternion::setX(float a) noexcept
{
	this->x = a;
}

void Quaternion::setY(float b) noexcept
{
	this->y = b;
}

void Quaternion::setZ(float c) noexcept
{
	this->z = c;
}

void Quaternion::setW(float d) noexcept
{
	this->w = d;
}

float Quaternion::getX() const noexcept
{
	return this->x;
}

float Quaternion::getY() const noexcept
{
	return this->y;
}

float Quaternion::getZ() const noexcept
{
	return this->z;
}

float Quaternion::getW() const noexcept
{
	return this->w;
}

float Quaternion::length() const noexcept
{
	return std::sqrt(x * x + y * y + z * z + w * w);
}

Quaternion Quaternion::normalize() const noexcept
{
	float len = length();
	if (len == 0)
		len = 1;
	return { x / len, y / len, z / len, w / len };
}

Quaternion Quaternion::conjugate() const noexcept
{
	return { -x, -y, -z, w };
}

Quaternion Quaternion::operator+(const Quaternion &v) const noexcept
{
	return { x + v.x, y + v.y, z + v.z, w + v.w };
}

Quaternion Quaternion::operator-(const Quaternion &v) const noexcept
{
	return { x - v.x, y - v.y, z - v.z, w - v.w };
}

Quaternion Quaternion::operator*(const Quaternion &v) const noexcept
{
	return { w * v.x + x * v.w + y * v.z - z * v.y,
		 w * v.y - x * v.z + y * v.w + z * v.x,
		 w * v.z + x * v.y - y * v.x + z * v.w,
		 w * v.w - x * v.x - y * v.y - z * v.z };
}

Quaternion Quaternion::operator*(const Vector3f &v) const noexcept
{
	return { w * v.getX() + y * v.getZ() - z * v.getY(),
		 w * v.getY() + z * v.getX() - x * v.getZ(),
		 w * v.getZ() + x * v.getY() - y * v.getX(),
		 -x * v.getX() - y * v.getY() - z * v.getZ() };
}

Quaternion Quaternion::operator/(const Quaternion &v) const noexcept
{
	return { x / v.x, y / v.y, z / v.z, w / v.w };
}

Quaternion Quaternion::operator+(const float r) const noexcept
{
	return { x + r, y + r, z + r, w + r };
}

Quaternion Quaternion::operator-(const float r) const noexcept
{
	return { x - r, y - r, z - r, w - r };
}

Quaternion Quaternion::operator*(const float r) const noexcept
{
	return { x * r, y * r, z * r, w * r };
}

Quaternion Quaternion::operator/(const float r) const noexcept
{
	return { x / r, y / r, z / r, w / r };
}

Quaternion &Quaternion::operator+=(const Quaternion &v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	w += v.w;
	return *this;
}

Quaternion &Quaternion::operator-=(const Quaternion &v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	w -= v.w;
	return *this;
}

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

Quaternion &Quaternion::operator/=(const Quaternion &v)
{
	x /= v.x;
	y /= v.y;
	z /= v.z;
	w /= v.w;
	return *this;
}

Quaternion &Quaternion::operator+=(const float r)
{
	x += r;
	y += r;
	z += r;
	w += r;
	return *this;
}

Quaternion &Quaternion::operator-=(const float r)
{
	x -= r;
	y -= r;
	z -= r;
	w -= r;
	return *this;
}

Quaternion &Quaternion::operator*=(const float r)
{
	x *= r;
	y *= r;
	z *= r;
	w *= r;
	return *this;
}

Quaternion &Quaternion::operator/=(const float r)
{
	x /= r;
	y /= r;
	z /= r;
	w /= r;
	return *this;
}

Vector3f Quaternion::get_forward() const
{
	return Vector3f{ 0, 0, 1 }.rotate(this->get());
}

Vector3f Quaternion::get_backward() const
{
	return Vector3f{ 0, 0, -1 }.rotate(this->get());
}

Vector3f Quaternion::get_up() const
{
	return Vector3f{ 0, -1, 0 }.rotate(this->get());
}

Vector3f Quaternion::get_down() const
{
	return Vector3f{ 0, -1, 0 }.rotate(this->get());
}

Vector3f Quaternion::get_right() const
{
	return Vector3f{ 1, 0, 0 }.rotate(this->get());
}

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

// Ken Shoemake's "Quaternion Calculus and Fast Animation"
Quaternion::Quaternion(const Matrix4f &matrix)
{
	float trace = matrix.get(0, 0) + matrix.get(1, 1) + matrix.get(2, 2);

	if (trace > 0) {
		float s = 0.5f / std::sqrt(trace + 1.0f);
		w = 0.25f / s;
		x = (matrix.get(1, 2) - matrix.get(2, 1)) * s;
		y = (matrix.get(2, 0) - matrix.get(0, 2)) * s;
		z = (matrix.get(0, 1) - matrix.get(1, 0)) * s;
	} else {
		if (matrix.get(0, 0) > matrix.get(1, 1) &&
		    matrix.get(0, 0) > matrix.get(2, 2)) {
			float s = 2.0f * std::sqrt(1.0f + matrix.get(0, 0) -
						   matrix.get(1, 1) -
						   matrix.get(2, 2));
			w = (matrix.get(1, 2) - matrix.get(2, 1)) / s;
			x = 0.25f * s;
			y = (matrix.get(1, 0) + matrix.get(0, 1)) / s;
			z = (matrix.get(2, 0) + matrix.get(0, 2)) / s;
		} else if (matrix.get(1, 1) > matrix.get(2, 2)) {
			float s = 2.0f * std::sqrt(1.0f + matrix.get(1, 1) -
						   matrix.get(0, 0) -
						   matrix.get(2, 2));
			w = (matrix.get(2, 0) - matrix.get(0, 2)) / s;
			x = (matrix.get(1, 0) + matrix.get(0, 1)) / s;
			y = 0.25f * s;
			z = (matrix.get(2, 1) + matrix.get(1, 2)) / s;
		} else {
			float s = 2.0f * std::sqrt(1.0f + matrix.get(2, 2) -
						   matrix.get(0, 0) -
						   matrix.get(1, 1));
			w = (matrix.get(0, 1) - matrix.get(1, 0)) / s;
			x = (matrix.get(2, 0) + matrix.get(0, 2)) / s;
			y = (matrix.get(1, 2) + matrix.get(2, 1)) / s;
			z = 0.25f * s;
		}
	}

	float length = std::sqrt(x * x + y * y + z * z + w * w);
	x /= length;
	y /= length;
	z /= length;
	w /= length;
}

Quaternion Quaternion::nlerp(Quaternion dest, float lerpFactor, bool shortest)
{
	Quaternion correctedDest = dest;

	if (shortest && this->dot(dest) < 0)
		correctedDest = Quaternion(-dest.getX(), -dest.getY(),
					   -dest.getZ(), -dest.getW());

	return (((correctedDest - (*this)) * lerpFactor) + (*this)).normalize();
}

Quaternion Quaternion::slerp(Quaternion dest, float lerpFactor, bool shortest)
{
	static const float EPSILON = 1e3f;

	float cos = this->dot(dest);
	Quaternion correctedDest = dest;

	if (shortest && cos < 0) {
		cos = -cos;
		correctedDest = Quaternion(-dest.getX(), -dest.getY(),
					   -dest.getZ(), -dest.getW());
	}

	if (std::abs(cos) >= 1 - EPSILON)
		return nlerp(correctedDest, lerpFactor, false);

	float sin = std::sqrt(1.0f - cos * cos);
	float angle = std::atan2(sin, cos);
	float invSin = 1.0f / sin;

	float srcFactor = std::sin((1.0f - lerpFactor) * angle) * invSin;
	float destFactor = std::sin((lerpFactor)*angle) * invSin;

	return ((*this * srcFactor) + correctedDest) * destFactor;
}

float Quaternion::dot(const Quaternion &r) const noexcept
{
	return x * r.getX() + y * r.getY() + z * r.getZ() + w * r.getW();
}
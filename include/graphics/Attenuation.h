#pragma once

#include <math/Vector3f.h>

struct Attenuation : private Vector3f {
    public:
	Attenuation() {};
	Attenuation(const Vector3f &vector)
		: Vector3f(vector) {};
	Attenuation(float constant, float linear, float exponent)
		: Vector3f(constant, linear, exponent) {};

	using Vector3f::get;
	float get_constant() const noexcept
	{
		return getX();
	}

	float get_linear() const noexcept
	{
		return getY();
	}

	float get_exponent() const noexcept
	{
		return getZ();
	}

	void set_constant(float constant) noexcept
	{
		setX(constant);
	}

	void set_linear(float linear) noexcept
	{
		setY(linear);
	}

	void set_exponent(float exponent) noexcept
	{
		setZ(exponent);
	}
};
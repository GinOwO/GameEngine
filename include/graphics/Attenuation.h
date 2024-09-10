#pragma once

struct Attenuation {
	float linear;
	float constant;
	float exponent;

	Attenuation()
	{
	}

	Attenuation(float constant, float linear, float exponent)
		: linear(linear)
		, constant(constant)
		, exponent(exponent)
	{
	}
};
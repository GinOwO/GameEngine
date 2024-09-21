#pragma once

struct Specular {
	float intensity;
	float exponent;

	static const std::function<void(void *)> deleter;

	Specular()
		: intensity(0)
		, exponent(0) {};

	Specular(float intensity, float exponent)
		: intensity(intensity)
		, exponent(exponent) {};
};
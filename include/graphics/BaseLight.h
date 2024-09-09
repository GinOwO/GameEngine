#pragma once

#include <math/Vector3f.h>

struct BaseLight {
	Vector3f color;
	float intensity;

	BaseLight(const Vector3f &c, const float &i)
		: color(c)
		, intensity(i)
	{
	}
	BaseLight()
	{
	}
};
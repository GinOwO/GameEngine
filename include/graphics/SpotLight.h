#pragma once

#include <math/Vector3f.h>
#include <graphics/PointLight.h>

struct SpotLight {
	PointLight point_light;
	Vector3f direction;
	float cutoff;

	SpotLight()
	{
	}

	SpotLight(PointLight point_light, Vector3f direction, float cutoff)
		: point_light(point_light)
		, direction(direction.normalize())
		, cutoff(cutoff)
	{
	}

	void set_direction(const Vector3f &direction)
	{
		this->direction = direction.normalize();
	}
};
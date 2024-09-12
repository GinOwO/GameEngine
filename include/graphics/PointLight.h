#pragma once

#include <math/Vector3f.h>

#include <graphics/BaseLight.h>
#include <graphics/Attenuation.h>

struct PointLight {
	BaseLight base_light;
	Attenuation attenuation;
	Vector3f position;
	float range;

	PointLight()
	{
	}

	PointLight(const BaseLight &base_light, const Attenuation &attenuation,
		   const Vector3f &position, float range)
		: base_light(base_light)
		, attenuation(attenuation)
		, position(position)
		, range(range)
	{
	}
};
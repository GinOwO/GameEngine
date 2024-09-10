#pragma once

#include <Vector3f.h>
#include <BaseLight.h>
#include <Attenuation.h>

struct PointLight {
	BaseLight base_light;
	Attenuation attenuation;
	Vector3f position;

	PointLight()
	{
	}

	PointLight(const BaseLight &base_light, const Attenuation &attenuation,
		   const Vector3f &position)
		: base_light(base_light)
		, attenuation(attenuation)
		, position(position)
	{
	}
};
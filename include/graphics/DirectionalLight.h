#pragma once

#include <math/Vector3f.h>

#include <graphics/BaseLight.h>

struct DirectionalLight {
	BaseLight base_light;
	Vector3f direction;

	DirectionalLight(const BaseLight &b, const Vector3f &d)
		: base_light(b)
		, direction(d.normalize())
	{
	}

	DirectionalLight()
	{
	}

	void set_direction(const Vector3f &direction)
	{
		this->direction = direction.normalize();
	}
};
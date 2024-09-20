#pragma once

#include <math/Vector3f.h>

#include <graphics/ForwardDirectional.h>

#include <components/BaseLight.h>
#include <components/SharedGlobals.h>

#include <string>

struct DirectionalLight : public BaseLight {
	DirectionalLight(const Vector3f &color, const float &intensity)
		: BaseLight(color, intensity)
	{
		shader = &ForwardDirectional::get_instance();
	}

	DirectionalLight(const std::string &hex, const float &intensity)
		: BaseLight(hex, intensity)
	{
		shader = &ForwardDirectional::get_instance();
	}

	DirectionalLight() = default;
};

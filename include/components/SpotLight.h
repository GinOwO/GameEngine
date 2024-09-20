

#pragma once

#include <math/Vector3f.h>

#include <graphics/Attenuation.h>
#include <graphics/ForwardSpot.h>

#include <components/PointLight.h>

#include <string>

struct SpotLight : public PointLight {
	SpotLight() = default;

	SpotLight(const Vector3f &color, const float &intensity,
		  const Attenuation &attenuation, float cutoff)
		: PointLight(color, intensity, attenuation)
	{
		this->cutoff = cutoff;
		this->shader = &ForwardSpot::get_instance();
	}

	SpotLight(const std::string &hex, const float &intensity,
		  const Attenuation &attenuation, float cutoff)
		: PointLight(hex, intensity, attenuation)
	{
		this->cutoff = cutoff;
		this->shader = &ForwardSpot::get_instance();
	}
};

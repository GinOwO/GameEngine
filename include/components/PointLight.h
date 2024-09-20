

#pragma once

#include <math/Vector3f.h>

#include <graphics/ForwardPoint.h>

#include <components/BaseLight.h>
#include <components/SharedGlobals.h>

#include <cmath>
#include <string>
#include <algorithm>

struct PointLight : public BaseLight {
	const int COLOR_DEPTH = 1 << 16; // TODO: comment

	PointLight() = default;

	PointLight(const Vector3f &color, const float &intensity,
		   const Attenuation &attenuation)
		: BaseLight(color, intensity)
	{
		this->attenuation = attenuation;

		auto [c, b, a] = attenuation.get();
		auto [d, e, f] = color.get();
		c -= COLOR_DEPTH * intensity * std::max(d, std::max(e, f));

		this->range = (-b + std::sqrt(b * b - 4 * a * c)) / (2 * a);

		this->shader = &ForwardPoint::get_instance();
	}

	PointLight(const std::string &color, const float &intensity,
		   const Attenuation &attenuation)
		: BaseLight(color, intensity)
	{
		this->attenuation = attenuation;
		this->range = 1000.0f;
		this->shader = &ForwardPoint::get_instance();
	}
};

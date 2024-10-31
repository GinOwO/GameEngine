#pragma once

#include <math/Vector3f.h>

#include <graphics/Shader.h>
#include <graphics/Attenuation.h>

#include <components/GameComponent.h>
#include <components/SharedGlobals.h>

#include <string>
#include <sstream>
#include <iomanip>
#include <exception>

struct BaseLight : public GameComponent {
	// Point Light
	Attenuation attenuation;
	Vector3f position;
	float range;

	// Spot Light
	float cutoff;

	Vector3f color;

	float intensity;

	Shader *shader;

	BaseLight(const Vector3f &color, const float &intensity)
		: intensity(intensity)
	{
		float red = color.getX(), green = color.getY(),
		      blue = color.getZ();
		if (red > 1)
			red /= 255.0f;
		if (green > 1)
			green /= 255.0f;
		if (blue > 1)
			blue /= 255.0f;
		this->color = { red, green, blue };
	}

	BaseLight(const std::string &hex, const float &intensity)
		: intensity(intensity)
	{
		uint32_t red = 0, green = 0, blue = 0;

		std::string hex_value = hex;
		if (hex_value[0] == '#') {
			hex_value = hex_value.substr(1);
		}

		if (hex_value.size() == 3) {
			hex_value = { hex_value[0], hex_value[0], hex_value[1],
				      hex_value[1], hex_value[2], hex_value[2] };
		}

		if (hex_value.size() == 6) {
			std::stringstream ss;
			ss << std::hex << hex_value;
			uint32_t hex_rgb;
			ss >> hex_rgb;
			red = (hex_rgb >> 16) & 0xFF;
			green = (hex_rgb >> 8) & 0xFF;
			blue = hex_rgb & 0xFF;
		} else {
			throw std::invalid_argument("Invalid HEX color format");
		}

		this->color =
			Vector3f(red / 255.0f, green / 255.0f, blue / 255.0f);
	}

	BaseLight()
		: color(0, 0, 0)
		, intensity(0.0f)
	{
	}

	void add_to_rendering_engine(bool id) override
	{
		SharedGlobals::get_instance().add_to_lights(
			static_cast<void *>(this));
	}

    private:
	void input(float delta) override {};
	void update(float delta) override {};
	void render(Shader &shader) override {};
};

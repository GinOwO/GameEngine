#include <components/LightSources.h>

LightSources &LightSources::get_instance()
{
	static LightSources instance;
	return instance;
}

void LightSources::add_to_directional_lights(void *light) noexcept
{
	directional_lights.push_back(light);
}

void LightSources::add_to_point_lights(void *light) noexcept
{
	point_lights.push_back(light);
}

void LightSources::add_to_spot_lights(void *light) noexcept
{
	spot_lights.push_back(light);
}

std::vector<void *> &LightSources::get_directional_lights()
{
	return directional_lights;
}

std::vector<void *> &LightSources::get_point_lights()
{
	return point_lights;
}

std::vector<void *> &LightSources::get_spot_lights()
{
	return spot_lights;
}

void LightSources::clear_lights()
{
	directional_lights.clear();
	point_lights.clear();
	spot_lights.clear();
	active_directional_light = active_spot_light = active_point_light =
		nullptr;
}

LightSources::LightSources()
{
}
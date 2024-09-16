#include <components/LightSources.h>

LightSources &LightSources::get_instance()
{
	static LightSources instance;
	return instance;
}

void LightSources::add_to_lights(void *light) noexcept
{
	lights.push_back(light);
}

std::vector<void *> &LightSources::get_lights()
{
	return lights;
}

void LightSources::clear_lights()
{
	lights.clear();
	active_light = nullptr;
}

LightSources::LightSources()
{
}
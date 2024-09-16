#include <components/SharedGlobals.h>

SharedGlobals &SharedGlobals::get_instance()
{
	static SharedGlobals instance;
	return instance;
}

void SharedGlobals::add_to_lights(void *light) noexcept
{
	lights.push_back(light);
}

std::vector<void *> &SharedGlobals::get_lights()
{
	return lights;
}

void SharedGlobals::clear_lights()
{
	lights.clear();
	active_light = nullptr;
}

SharedGlobals::SharedGlobals()
{
}
// TODO: Comment
#pragma once

#include <math/Vector3f.h>

#include <vector>

class LightSources {
    public:
	LightSources(const LightSources &) = delete;
	LightSources &operator=(const LightSources &) = delete;

	static LightSources &get_instance();

    private:
	LightSources();
	std::vector<void *> directional_lights, point_lights, spot_lights;

    public:
	Vector3f ambient_light; /**< Light responsible for ambient lighting. */
	void *active_directional_light;
	void *active_point_light;
	void *active_spot_light;

	void add_to_directional_lights(void *light) noexcept;
	void add_to_point_lights(void *light) noexcept;
	void add_to_spot_lights(void *light) noexcept;
	std::vector<void *> &get_directional_lights();
	std::vector<void *> &get_point_lights();
	std::vector<void *> &get_spot_lights();
	void clear_lights();
};
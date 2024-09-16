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
	std::vector<void *> lights;

    public:
	Vector3f active_ambient_light; /**< Light responsible for ambient lighting. */
	void *active_light;

	void add_to_lights(void *light) noexcept;
	std::vector<void *> &get_lights();
	void clear_lights();
};
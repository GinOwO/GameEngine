// TODO: Comment
#pragma once

#include <math/Vector3f.h>

#include <unordered_set>

class SharedGlobals {
    public:
	SharedGlobals(const SharedGlobals &) = delete;
	SharedGlobals &operator=(const SharedGlobals &) = delete;

	static SharedGlobals &get_instance();

    private:
	SharedGlobals();
	std::unordered_set<void *> lights;

    public:
	Vector3f active_ambient_light;
	void *active_light = nullptr;
	void *main_camera = nullptr;
	int w_width = 1, w_height = 1;
	bool resized = false;
	void *window = nullptr;

	void add_to_lights(void *light) noexcept;
	std::unordered_set<void *> &get_lights();
	void clear_lights();
};
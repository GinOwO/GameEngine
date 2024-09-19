// TODO: Comment
#pragma once

#include <math/Vector3f.h>
#include <math/Transform.h>

#include <vector>

class SharedGlobals {
    public:
	SharedGlobals(const SharedGlobals &) = delete;
	SharedGlobals &operator=(const SharedGlobals &) = delete;

	static SharedGlobals &get_instance();

    private:
	SharedGlobals();
	std::vector<void *> lights;

    public:
	Vector3f active_ambient_light; /**< Light responsible for ambient lighting. */
	void *active_light;
	void *main_camera;

	void add_to_lights(void *light) noexcept;
	std::vector<void *> &get_lights();
	void clear_lights();
};
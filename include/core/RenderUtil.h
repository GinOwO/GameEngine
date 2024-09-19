#pragma once

#include <math/Vector3f.h>

class RenderUtil {
    public:
	static void clear_screen();
	static void init_graphics();
	static void texture_enable(bool enable = true);
	static void set_clear_color(const Vector3f &color);
	static void unbind_textures();
};
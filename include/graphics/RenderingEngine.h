#pragma once

#include <game/GameObject.h>

#include <core/Camera.h>

class RenderingEngine {
    public:
	RenderingEngine(const RenderingEngine &) = delete;
	RenderingEngine &operator=(const RenderingEngine &) = delete;

	static RenderingEngine &get_instance();

    private:
	Camera &camera;
	static void set_clear_color(const Vector3f &color);
	static void unbind_textures();
	static void texture_enable(bool enable = true);
	static void clear_screen();
	RenderingEngine();

    public:
	void render(GameObject *object);
};
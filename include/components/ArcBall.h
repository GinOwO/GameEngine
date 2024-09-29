#pragma once

#include <core/Input.h>
#include <core/Window.h>

#include <math/Vector3f.h>
#include <math/Quaternion.h>
#include <math/Transform.h>

#include <components/GameComponent.h>

#include <algorithm>
#include <cmath>

class ArcBall : public GameComponent {
	float radius;
	float sensitivity;
	float azimuth = 0.0f;
	float elevation = 0.0f;
	Transform *target;

    public:
	ArcBall(Transform *target = nullptr, float radius = 1.0f,
		float sensitivity = 0.01f)
		: radius(radius)
		, target(target)
		, sensitivity(sensitivity) {};

	void input(float delta) override
	{
		static Input &input_handler = Input::get_instance();

		if (target == nullptr)
			return;

		static bool flag = false;
		if (input_handler.is_mouse_down(GLFW_MOUSE_BUTTON_2)) {
			flag = true;
		}
		if (flag && input_handler.is_mouse_up(GLFW_MOUSE_BUTTON_2)) {
			flag = false;
		}

		const double(*mouse_pos)[2] = input_handler.get_mouse_pos();
		static double last_mouse_pos[2] = { mouse_pos[0][0],
						    mouse_pos[0][1] };
		if (flag) {
			float dx = (mouse_pos[0][0] - last_mouse_pos[0]) *
				   sensitivity;
			float dy = (mouse_pos[0][1] - last_mouse_pos[1]) *
				   -sensitivity;

			azimuth -= dx;
			elevation = std::clamp(elevation - dy, 0.1f, 3.0f);
		}

		last_mouse_pos[0] = mouse_pos[0][0];
		last_mouse_pos[1] = mouse_pos[0][1];
	}

	void update(float delta) override
	{
		if (target == nullptr)
			return;

		float x = radius * std::cos(elevation) * std::sin(azimuth);
		float y = radius * std::cos(elevation) * std::cos(azimuth);
		float z = radius * std::sin(elevation);

		Vector3f new_position =
			target->get_translation() + Vector3f{ x, y, z };
		get_parent_transform()
			->set_translation(new_position)
			.look_at(target->get_translation(), Vector3f::z_axis);
	}

	void render(Shader &) override {};
};

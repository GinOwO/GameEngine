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
	Transform *target;

    public:
	ArcBall(float radius = 1.0f, Transform *target = nullptr)
		: radius(radius)
		, target(target) {};

	void input(float delta) override
	{
		static Window &window = Window::get_instance();
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

		if (!flag)
			return;

		const float w = window.get_window_width();
		const float h = window.get_window_height();

		const double(*mouse_pos)[2] = input_handler.get_mouse_pos();

		float x0 = ((mouse_pos[0][0] - (w / 2)) / (w / 2)) * radius;
		float z0 = ((mouse_pos[0][1] - (h / 2)) / (h / 2)) * radius;
		float x1 = ((mouse_pos[1][0] - (w / 2)) / (w / 2)) * radius;
		float z1 = ((mouse_pos[1][1] - (h / 2)) / (h / 2)) * radius;

		float y0 = 0, y1 = 0;
		float dist0 = x0 * x0 + z0 * z0, dist1 = x1 * x1 + z1 * z1;
		if (dist0 <= radius * radius) {
			y0 = std::sqrt(radius * radius - dist0);
		}
		if (dist1 <= radius * radius) {
			y1 = std::sqrt(radius * radius - dist1);
		}

		Vector3f prev_pos{ x0, y0, z0 };
		Vector3f new_pos{ x1, y1, z1 };

		if (prev_pos.is_close(new_pos, 1e-2))
			return;

		prev_pos = prev_pos.normalize();
		new_pos = new_pos.normalize();
		Vector3f rotation_axis = prev_pos.cross(new_pos).normalize();

		float cosine = prev_pos.dot(new_pos);
		float theta = std::acos(std::clamp(cosine, -1.0f, 1.0f));

		std::cout << (theta * 180.0f / M_PI) << '\n';
		// if (theta * 180.0f / M_PI < 2.0f)
		// 	return;

		get_parent_transform()->rotate(rotation_axis, theta);
	}

	void update(float delta) override
	{
		if (target == nullptr)
			return;

		Vector3f direction = get_parent_transform()->get_translation() -
				     target->get_translation();
		direction = direction.normalize();

		Vector3f new_position =
			target->get_translation() + direction * radius;
		get_parent_transform()->set_translation(new_position);
	}

	void render(Shader &) override {};
};

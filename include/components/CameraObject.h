#pragma once

#include <math/Vector2f.h>
#include <math/Vector3f.h>
#include <math/Transform.h>
#include <math/Quaternion.h>

#include <components/GameObject.h>
#include <components/GameComponent.h>
#include <core/SharedGlobals.h>
#include <components/Camera.h>
#include <components/FreeLook.h>
#include <components/FreeMove.h>
#include <components/FollowComponent.h>
#include <components/LookAtComponent.h>

#define CAMERA_DEBUG 0

#include <iostream>

class CameraObject : public GameObject {
	float fov;
	Quaternion init_rotation;

    public:
	Camera *camera;

	CameraObject(float fov = 70.0f, const Vector3f &offset = { 0, 0, 0 },
		     const Quaternion &init_rotation = { 0, 0, 0, 1 },
		     const Vector3f &free_move = { 1 },
		     const Vector2f &free_look = { 1, 1 },
		     Transform *player_transform = nullptr)
		: camera(new Camera())
		, init_rotation(init_rotation)
		, fov(fov)
	{
		if (free_move != Vector3f{ 0 }) {
			this->add_component(new FreeMove(free_move.getX(),
							 free_move.getY(),
							 free_move.getZ()));
		}

		if (free_look.getX() != 0 || free_look.getY() != 0) {
			this->add_component(new FreeLook(free_look.getX(),
							 free_look.getY()));
		}

		this->add_component(camera)->add_component(
			new FollowComponent(offset, player_transform));

		camera->set_projection(to_radians(fov), 1.0f, .1f, 1000.0f);
	}

	void update(float delta) override
	{
		SharedGlobals &globals = SharedGlobals::get_instance();
		if (globals.resized) {
			camera->set_projection(to_radians(fov),
					       globals.w_height /
						       globals.w_height,
					       .1f, 1000.0f);
			this->transform.set_rotation(init_rotation);
			globals.resized = false;
		}
		debug();
		GameObject::update(delta);
	}

	void debug()
	{
#if CAMERA_DEBUG
		Quaternion q = transform.get_rotation();
		// Get the components of the quaternion
		float x = q.getX();
		float y = q.getY();
		float z = q.getZ();
		float w = q.getW();

		// Calculate roll (rotation around x-axis)
		float sinr_cosp = 2 * (w * x + y * z);
		float cosr_cosp = 1 - 2 * (x * x + y * y);
		float roll = std::atan2(sinr_cosp, cosr_cosp);

		// Calculate pitch (rotation around y-axis)
		float sinp = 2 * (w * y - z * x);
		float pitch;
		if (std::abs(sinp) >= 1)
			pitch = std::copysign(
				M_PI / 2,
				sinp); // use 90 degrees if out of range
		else
			pitch = std::asin(sinp);

		// Calculate yaw (rotation around z-axis)
		float siny_cosp = 2 * (w * z + x * y);
		float cosy_cosp = 1 - 2 * (y * y + z * z);
		float yaw = std::atan2(siny_cosp, cosy_cosp);

		// Convert from radians to degrees for easier readability
		roll = roll * (180.0 / M_PI);
		pitch = pitch * (180.0 / M_PI);
		yaw = yaw * (180.0 / M_PI);

		// Output the Euler angles
		std::cout << "Euler Angles (degrees):" << '\n';
		std::cout << "Roll:  " << roll << '\n';
		std::cout << "Pitch: " << pitch << '\n';
		std::cout << "Yaw:   " << yaw << '\n';
		std::cout << "WXYZ:  " << w << " " << x << " " << y << " " << z
			  << '\n';
#endif // CAMERA_DEBUG
	}
};
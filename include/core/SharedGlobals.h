#pragma once

#include <math/Vector3f.h>

#include <btBulletDynamicsCommon.h>

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
	btDiscreteDynamicsWorld *dynamics_world;
	btAlignedObjectArray<btCollisionShape *> collision_shapes;
	std::vector<btRigidBody *> rigid_bodies;
	btRigidBody *current_rigid_body = nullptr;
	const int32_t GRAVITY = 1.0f;

	Vector3f active_ambient_light;
	void *active_light = nullptr;
	void *main_camera = nullptr;
	int32_t w_width = 1, w_height = 1;
	bool resized = false;
	void *window = nullptr;
	static void *player_entity, *enemy_entity;

	void add_to_lights(void *light) noexcept;
	std::unordered_set<void *> &get_lights();
	void clear_lights();

#ifdef MULTIPLAYER
	void *enemy_moves = nullptr; // SafeQueue<pair<action, delta>>
	void *player_moves = nullptr; // SafeQueue<pair<action, delta>>
#endif
};
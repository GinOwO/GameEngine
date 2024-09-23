#include <components/SharedGlobals.h>

#include <unordered_set>

SharedGlobals &SharedGlobals::get_instance()
{
	static SharedGlobals instance;
	return instance;
}

void SharedGlobals::add_to_lights(void *light) noexcept
{
	lights.insert(light);
}

std::unordered_set<void *> &SharedGlobals::get_lights()
{
	return lights;
}

void SharedGlobals::clear_lights()
{
	lights.clear();
	active_light = nullptr;
}

SharedGlobals::SharedGlobals()
{
	// Bullet initialization
	btBroadphaseInterface *broadphase = new btDbvtBroadphase();
	btDefaultCollisionConfiguration *collision_configuration =
		new btDefaultCollisionConfiguration();
	btCollisionDispatcher *dispatcher =
		new btCollisionDispatcher(collision_configuration);
	btSequentialImpulseConstraintSolver *solver =
		new btSequentialImpulseConstraintSolver();

	dynamics_world = new btDiscreteDynamicsWorld(
		dispatcher, broadphase, solver, collision_configuration);
	dynamics_world->setGravity(btVector3(0, -9.81f, 0));
}
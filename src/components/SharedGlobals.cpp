#include <components/SharedGlobals.h>

#include <physics/Collision.h>

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

void collision_near_callback(btBroadphasePair &collisionPair,
			     btCollisionDispatcher &dispatcher,
			     const btDispatcherInfo &dispatchInfo)
{
	const btCollisionObject *colObj0 =
		static_cast<const btCollisionObject *>(
			collisionPair.m_pProxy0->m_clientObject);
	const btCollisionObject *colObj1 =
		static_cast<const btCollisionObject *>(
			collisionPair.m_pProxy1->m_clientObject);

	GameObject *obj0 = static_cast<GameObject *>(colObj0->getUserPointer());
	GameObject *obj1 = static_cast<GameObject *>(colObj1->getUserPointer());

	if (obj0 && obj1) {
		static CollisionCallback collisionCallback;
		dispatcher.defaultNearCallback(collisionPair, dispatcher,
					       dispatchInfo);
		obj0->handle_collision(obj1);
		obj1->handle_collision(obj0);
	}
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
	dynamics_world->setGravity(btVector3(0, 0, -9.81f));

	// Register collision near callback
	dispatcher->setNearCallback(collision_near_callback);
}

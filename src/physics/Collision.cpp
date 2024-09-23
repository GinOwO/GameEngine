#include <physics/Collision.h>

#include <components/Person.h>
#include <components/Terrain.h>

btScalar CollisionCallback::addSingleResult(
	btManifoldPoint &cp, const btCollisionObjectWrapper *colObj0Wrap,
	int partId0, int index0, const btCollisionObjectWrapper *colObj1Wrap,
	int partId1, int index1)
{
	const btCollisionObject *obj0 = colObj0Wrap->getCollisionObject();
	const btCollisionObject *obj1 = colObj1Wrap->getCollisionObject();

	if (obj0->getUserPointer() && obj1->getUserPointer()) {
		handle_collision((GameObject *)obj0->getUserPointer(),
				 (GameObject *)obj1->getUserPointer());
	}

	btVector3 collisionPoint = cp.getPositionWorldOnA();
	btVector3 collisionNormal = cp.m_normalWorldOnB;
	btScalar impulse = cp.m_appliedImpulse;

	return 0;
}

void CollisionCallback::handle_collision(GameObject *obj0, GameObject *obj1)
{
	if (dynamic_cast<Person *>(obj0) && dynamic_cast<Terrain *>(obj1)) {
		static_cast<Person *>(obj0)->on_ground = true;
	} else if (dynamic_cast<Terrain *>(obj0) &&
		   dynamic_cast<Person *>(obj1)) {
		static_cast<Person *>(obj1)->on_ground = true;
	}
}
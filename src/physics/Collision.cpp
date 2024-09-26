#include <physics/Collision.h>

btScalar CollisionCallback::addSingleResult(
	btManifoldPoint &cp, const btCollisionObjectWrapper *colObj0Wrap,
	int partId0, int index0, const btCollisionObjectWrapper *colObj1Wrap,
	int partId1, int index1)
{
	const btCollisionObject *obj0 = colObj0Wrap->getCollisionObject();
	const btCollisionObject *obj1 = colObj1Wrap->getCollisionObject();

	btVector3 collisionPoint = cp.getPositionWorldOnA();
	btVector3 collisionNormal = cp.m_normalWorldOnB;
	btScalar impulse = cp.m_appliedImpulse;

	return 0;
}
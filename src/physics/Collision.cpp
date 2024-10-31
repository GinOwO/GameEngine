#include <physics/Collision.h>

btScalar
CollisionCallback::addSingleResult(btManifoldPoint &cp,
				   const btCollisionObjectWrapper *colObj0Wrap,
				   int32_t partId0, int32_t index0,
				   const btCollisionObjectWrapper *colObj1Wrap,
				   int32_t partId1, int32_t index1)
{
	const btCollisionObject *obj0 = colObj0Wrap->getCollisionObject();
	const btCollisionObject *obj1 = colObj1Wrap->getCollisionObject();

	btVector3 collisionPoint = cp.getPositionWorldOnA();
	btVector3 collisionNormal = cp.m_normalWorldOnB;
	btScalar impulse = cp.m_appliedImpulse;

	return 0;
}
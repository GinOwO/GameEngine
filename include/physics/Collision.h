#pragma once

#include <btBulletDynamicsCommon.h>

#include <components/GameObject.h>

#include <iostream>

class CollisionCallback : public btCollisionWorld::ContactResultCallback {
    public:
	btScalar addSingleResult(btManifoldPoint &cp,
				 const btCollisionObjectWrapper *colObj0Wrap,
				 int32_t partId0, int32_t index0,
				 const btCollisionObjectWrapper *colObj1Wrap,
				 int32_t partId1, int32_t index1) override;
};
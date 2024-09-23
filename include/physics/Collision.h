#pragma once

#include <btBulletDynamicsCommon.h>

#include <components/GameObject.h>

#include <iostream>

class CollisionCallback : public btCollisionWorld::ContactResultCallback {
    public:
	btScalar addSingleResult(btManifoldPoint &cp,
				 const btCollisionObjectWrapper *colObj0Wrap,
				 int partId0, int index0,
				 const btCollisionObjectWrapper *colObj1Wrap,
				 int partId1, int index1) override;

	void handle_collision(GameObject *obj0, GameObject *obj1);
};
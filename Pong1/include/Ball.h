#pragma once
#include "ECS.h"
#include "EventSystem.h"
class Ball : public Entity {
protected:
	Subscriber<Entity *> * actionOnCollision;
	virtual void OnCollission(Entity * entityPtr);
public:
	Ball(float x, float y);
	virtual ~Ball();
	BaseSubscriber * getCollisionSubscriber();
	virtual void resetSpeed();
};
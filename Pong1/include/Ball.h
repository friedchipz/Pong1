#pragma once
#include "ECS.h"
#include "EventSystem.h"
class Ball : public Entity {
protected:
	virtual void actOnCollision(Entity * entityPtr);
public:
	Ball(float x, float y);
	virtual ~Ball() = default;
	virtual void resetSpeed();
};
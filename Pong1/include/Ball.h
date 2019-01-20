#pragma once
#include "ECS.h"
class Ball : public Entity {
protected:
public:
	Ball(float x, float y);
	virtual ~Ball();
	virtual void OnCollission(Entity * entityPtr);
	virtual void resetSpeed();
};
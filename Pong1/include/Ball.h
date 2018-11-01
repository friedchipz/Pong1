#pragma once
#include "Entity.h"
class Ball : public Entity
{
protected:
	float speed, angle;
	virtual void update();
	virtual void render(SDL_Renderer * renderer);
	virtual void resetSpeed();
public:
	Ball(float x, float y);
	virtual void eventCollission(Entity * entityPtr);
	virtual ~Ball();
};


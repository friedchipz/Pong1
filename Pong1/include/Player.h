#pragma once
#include "Entity.h"
class Player : public Entity {
protected:
	float speedFactor;
	float maxSpeed;
	float acceleration;
	SDL_Keycode up, down;
protected:
	virtual void update();
	virtual void render(SDL_Renderer * renderer);
	virtual void handleEvent(const SDL_Event & event);
public:
	Player(float x, float y, const SDL_Keycode up, const SDL_Keycode down);
	void setInputEventUp(const SDL_Keycode up);
	void setInputEventDown(const SDL_Keycode down);
	virtual ~Player();
};


#pragma once
#include <SDL.h>

class GameMode;

class Entity {
	friend class GameMode;
public:
	float posX, posY;
	float height, width;
protected:
	virtual void update();
	virtual void render(SDL_Renderer * renderer);
	virtual void handleEvent(const SDL_Event & event);
public:
	Entity() = default;
	virtual ~Entity() = default;
	const SDL_Rect getRect() const;
	virtual void eventCollission(Entity * entityPtr);
	static bool checkCollision(SDL_Rect r1, SDL_Rect r2);
};


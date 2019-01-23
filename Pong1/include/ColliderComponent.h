#pragma once
#include <functional>
#include <set>
#include <SDL.h>
#include "ECS.h"
#include "Maths.h"
#include "EventSystem.h"
class ColliderComponent : public Component {
protected:
	Event<Entity *> * eventCollision;
	Subscriber<Entity *> * onCollision;
public:
	SDL_Rect area;
	ColliderComponent(SDL_Rect area);
	ColliderComponent(Vector2d pos, Vector2d size);
	~ColliderComponent();
	SDL_Rect getTransformedArea() const;
	Event<Entity *> * getEventCollision() const;
	Subscriber<Entity *> * getOnCollision() const;
	bool checkCollission(ColliderComponent & checked);
	void collide(Entity * triggerer);
	static bool fromAbove(SDL_Rect ref, SDL_Rect body);
	static bool fromBelow(SDL_Rect ref, SDL_Rect body);
	static bool fromLeft(SDL_Rect ref, SDL_Rect body);
	static bool fromRight(SDL_Rect ref, SDL_Rect body);
};


#pragma once
#include <functional>
#include <set>
#include <SDL.h>
#include "ECS.h"
#include "Maths.h"
#include "EventSystem.h"
class ColliderComponent : public Component {
protected:
	//feels like subscribers
	Event<Entity *> * eventOnCollision;
	Subscriber<Entity *> * actionOnCollision;
	//std::set<std::function<void(Entity *)>> callBacks;
public:
	SDL_Rect area;
	ColliderComponent(SDL_Rect area);
	ColliderComponent(Vector2d pos, Vector2d size);
	~ColliderComponent();
	SDL_Rect getTransformedArea() const;
	Event<Entity *> * getEventOnCollision() const;
	Subscriber<Entity *> * getActionOnCollision() const;
	//feels like Event<Entity*>::Subscribe(Subscriber<Entity*> subscriber)
	//void addBinding(std::function<void(Entity *)> callback);
	//void delBinding(std::function<void(Entity *)> callback);
	bool checkCollission(ColliderComponent & checked);
	void collide(Entity * triggerer);
	static bool fromAbove(SDL_Rect ref, SDL_Rect body);
	static bool fromBelow(SDL_Rect ref, SDL_Rect body);
	static bool fromLeft(SDL_Rect ref, SDL_Rect body);
	static bool fromRight(SDL_Rect ref, SDL_Rect body);
};


#pragma once
#include <functional>
#include <set>
#include <SDL.h>
#include "ECS.h"
#include "Maths.h"
class ColliderComponent : public Component {
protected:
	std::set<std::function<void(Entity *)>> callBacks;
public:
	SDL_Rect area;
	ColliderComponent(SDL_Rect area);
	ColliderComponent(Vector2d pos, Vector2d size);
	~ColliderComponent() = default;
	SDL_Rect getTransformedArea();
	void addBinding(std::function<void(Entity *)> callback);
	void delBinding(std::function<void(Entity *)> callback);
	bool checkCollission(ColliderComponent & checked);
	void collide(Entity * triggerer);
	static bool fromAbove(SDL_Rect ref, SDL_Rect body);
	static bool fromBelow(SDL_Rect ref, SDL_Rect body);
	static bool fromLeft(SDL_Rect ref, SDL_Rect body);
	static bool fromRight(SDL_Rect ref, SDL_Rect body);
};


#pragma once
#include <SDL.h>
#include "ECS.h"
#include "TransformComponent.h"
class SolidRendererComponent : public Component {
public:
	SDL_Color fillColor;
	SDL_Rect area;
	SolidRendererComponent(SDL_Color fillColor, SDL_Rect area);
	~SolidRendererComponent() = default;
	virtual void render(SDL_Renderer * renderer);
};


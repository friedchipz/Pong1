#pragma once
#include "ECS.h"
#include "Maths.h"
class TransformComponent : public Component {
public:
	float x, y, scaleX, scaleY;
	Vector2d pos, scale;
	TransformComponent(float x = 0, float y = 0, float sx = 1, float sy = 1);
	TransformComponent(Vector2d pos = Vector2d(0, 0), Vector2d scale = Vector2d(1, 1));
	~TransformComponent();
	SDL_Rect transformRect(SDL_Rect rect);
};
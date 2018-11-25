#include "TransformComponent.h"

TransformComponent::TransformComponent(float x, float y, float sx, float sy) {
	pos = Vector2d(x, y);
	scale = Vector2d(sx, sy);
}
TransformComponent::TransformComponent(Vector2d pos, Vector2d scale){
	this->pos = pos;
	this->scale = scale;
}
TransformComponent::~TransformComponent(){}

SDL_Rect TransformComponent::transformRect(SDL_Rect rect){
	rect.x += pos.x;
	rect.y += pos.y;
	rect.w *= scale.x;
	rect.h *= scale.y;
	return rect;
}

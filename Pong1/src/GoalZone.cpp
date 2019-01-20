#include "GoalZone.h"

#include "TransformComponent.h"
#include "ColliderComponent.h"

GoalZone::GoalZone(float x0, float y0, float x1, float y1) {
	this->addComponent<TransformComponent>(x0, y0);
	this->addComponent<ColliderComponent>(SDL_Rect { 0, 0, (int)(x1 - x0), (int)(y1 - y0 )});
}

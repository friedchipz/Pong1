#include "../include/GoalZone.h"

#include "../include/TransformComponent.h"
#include "../include/ColliderComponent.h"

GoalZone::GoalZone(float x0, float y0, float x1, float y1) {
	this->addComponent<TransformComponent>(x0, y0);
	this->addComponent<ColliderComponent>(0, 0, x1 - x0, y1 - y0);
}

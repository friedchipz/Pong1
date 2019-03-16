#include "MovementComponent.h"

MovementComponent::MovementComponent(float maxSpeed){
	this->maxSpeed = maxSpeed;
	this->speed = Vector2d(0, 0);
	this->accelerationFactor = Vector2d(0, 0);
}

void MovementComponent::update(){
	if (accelerationFactor.length() > 1) accelerationFactor = accelerationFactor.normalize();
	speed = speed + accelerationFactor * maxSpeed;
	if (speed.length() > maxSpeed) speed = speed.normalize()*maxSpeed;
	entity->getComponent<TransformComponent>().pos = entity->getComponent<TransformComponent>().pos + speed;
}

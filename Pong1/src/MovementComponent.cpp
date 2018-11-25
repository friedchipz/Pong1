#include "..\include\MovementComponent.h"

MovementComponent::MovementComponent(float maxSpeed){
	this->maxSpeed = maxSpeed;
	this->speed = Vector2d(0, 0);
	this->accelerationFactor = Vector2d(0, 0);
}

void MovementComponent::update(){
	accelerationFactor = accelerationFactor.normalize();
	//speed.x = speed.x + accelerationFactor.x * maxSpeed;
	//speed.y = speed.y + accelerationFactor.y * maxSpeed;
	speed = speed + accelerationFactor * maxSpeed;
	if (speed.length() > maxSpeed) speed = speed.normalize()*maxSpeed;
	//TODO: check why this doesn't allow pos = pos +speed (move ctor involved)
	entity->getComponent<TransformComponent>().pos.x = entity->getComponent<TransformComponent>().pos.x + speed.x;
	entity->getComponent<TransformComponent>().pos.y = entity->getComponent<TransformComponent>().pos.y + speed.y;
}

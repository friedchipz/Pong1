#include "PolarMovementComponent.h"
#include "TransformComponent.h"
#include "Maths.h"
#include <math.h>

PolarMovementComponent::PolarMovementComponent(float maxSpeed, float maxAngularSpeed, float speed, float angle, float angularSpeed) {
	this->maxSpeed = maxSpeed;
	this->maxAngularSpeed = maxAngularSpeed;
	this->speed = speed;
	this->angle = angle;
	this->angularSpeed = angularSpeed;
	this->angularAccelFactor = 0;
	this->accelFactor = 0;
}

void PolarMovementComponent::bounceH(){
	angle = 180 - angle;
}

void PolarMovementComponent::bounceV(){
	angle = -angle;
}

void PolarMovementComponent::update(){
	Vector2d pos = entity->getComponent<TransformComponent>().pos;
	speed += accelFactor * maxSpeed;
	if (speed > maxSpeed) {
		speed = maxSpeed;
	}	else if (speed < 0) {
		speed = 0;
	}
	angularSpeed += angularAccelFactor * maxAngularSpeed;
	if (angularSpeed > maxAngularSpeed) {
		angularSpeed = maxAngularSpeed;
	} else if (angularSpeed < -maxAngularSpeed) {
		angularSpeed = -maxAngularSpeed;
	}
	angle += angularSpeed;
	if (angle > 360) {
		angle = angle - trunc(angle / 360) * 360;
	} else if (angle < 360) {
		angle = angle + trunc(-angle / 360) * 360;
	}
	pos.x += speed * cos(angle * M_PI / 180);
	pos.y += speed * sin(angle * M_PI / 180);
	entity->getComponent<TransformComponent>().pos = pos;
}

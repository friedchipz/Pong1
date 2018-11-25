#pragma once
#include "../include/ECS.h"
#include "../include/TransformComponent.h"
#include "../include/Maths.h"

class MovementComponent : public Component {
public:
	float maxSpeed;
	Vector2d speed;
	Vector2d accelerationFactor;
public:
	MovementComponent(float maxSpeed = 100);
	virtual void update();
	~MovementComponent() = default;
};


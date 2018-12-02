#pragma once
#include "ECS.h"
#include "TransformComponent.h"
#include "Maths.h"

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


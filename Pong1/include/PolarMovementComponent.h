#pragma once
#include "ECS.h"
class PolarMovementComponent : public Component {
public:
	float angle;
	float speed;
	float maxSpeed;
	float angularSpeed;
	float maxAngularSpeed;
	float accelFactor;
	float angularAccelFactor;

public:
	PolarMovementComponent(float maxSpeed = 100, float maxAngularSpeed = 3, float speed = 0, float angle=0, float angularSpeed = 0);
	~PolarMovementComponent() = default;
	void bounceH();
	void bounceV();
	virtual void update();
};


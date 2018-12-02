#pragma once
#include "ECS.h"
class GoalZone : public Entity {
public:
	GoalZone(float x0, float y0, float x1, float y1);
	~GoalZone()=default;
};


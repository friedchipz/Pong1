#pragma once
#include <SDL.h>
#include "ECS.h"
class Wall : public Entity{
public:
	Wall(float x0, float y0, float x1, float y1);
	~Wall() = default;
};


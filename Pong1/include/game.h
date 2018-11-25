#pragma once
#include <SDL.h>
#include "../include/GameMode.h"
#include "../include/Player.h"
#include "../include/Ball.h"
#include "../include/Wall.h"
#include "../include/GoalZone.h"
#include "CoreComponents.h"
class Game : public GameMode  {
private:
	//info about the game
	int p1Score, p2Score;
	Player * p1, * p2;
	Ball * ball;

	//private methods for the game
	virtual void init();
	void resetBall();
	void showScore();
	void scoreGoal(int player);

public:
	Game();
	~Game() = default;
};
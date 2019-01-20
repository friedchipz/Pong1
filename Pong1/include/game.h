#pragma once
#include <SDL.h>
#include "GameMode.h"
#include "Player.h"
#include "Ball.h"
#include "Wall.h"
#include "GoalZone.h"
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
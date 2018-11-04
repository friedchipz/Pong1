#pragma once
#include "SDL.h"
#include "GameMode.h"
#include "Player.h"
#include "Ball.h"
class Game : public GameMode  {
private:
	//info about the game
	int p1Score, p2Score;
	Player * p1, * p2;
	Ball * ball;

	//private methods for the game
	virtual void init();
	virtual void update();
	void resetBall();
	void showScore();

public:
	Game();
	~Game() = default;
};
#pragma once
#include "SDL.h"
class Game {
private:
	//info about the game
	int p1Score, p2Score;
	float p1PosX, p1PosY;
	float p2PosX, p2PosY;
	float p1Speed, p2Speed;
	float ballSpeed, ballAngle;
	float ballPosX, ballPosY;
	float ballWidth, ballHeight;
	bool finished;
	float playersMaxSpeed;
	int boardWidth, boardHeight;
	
	//data for rendering
	SDL_Window * window;
	SDL_Renderer * renderer;
	SDL_Rect p1Rect, p2Rect, ballRect;
	const int MAXFPS=60;
	const int frameDelay=1000/MAXFPS;
	Uint32 frameStart;
	int frameTime;

	//private methods for the game
	virtual void init();
	virtual void update();
	virtual void render();
	virtual void handleEvents();
	virtual void clean();

	void resetBall();
public:
	Game();
	~Game();
	void run();
	const bool isFinished() const;

};
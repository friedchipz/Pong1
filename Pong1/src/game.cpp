#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include <stdexcept>
#include <iostream>

#include "../include/game.h"
#include "SDL.h"

Game::Game() {
	ball = nullptr;
	p1 = nullptr;
	p2 = nullptr;
}

void Game::init() {
	GameMode::init();
	srand(time(NULL));
	p1Score = p2Score = 0;
	p1 = new Player(5, 215, SDLK_w, SDLK_s);
	registerEntity(p1);
	p2 = new Player(625, 215, SDLK_i, SDLK_k);
	registerEntity(p2);
	ball = new Ball(315, 235);
	registerEntity(ball);
}

void Game::update() {
	GameMode::update();
	//Goal conditions:
	if (ball->posX <= 0) {
		p2Score++;
		resetBall();
		showScore();
	} else if (ball->posX + ball->width >= 640) {
		p1Score++;
		resetBall();
		showScore();
	}
}

void Game::resetBall() {
	unregisterEntity(ball);
	ball = new Ball(320, 240);
	registerEntity(ball);
}

void Game::showScore() {
	std::cout << "Score: " << p1Score << " - " << p2Score << std::endl;
}

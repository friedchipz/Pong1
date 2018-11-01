#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include <stdexcept>
#include <iostream>

#include "game.h"
#include "SDL.h"

Game::Game(){
	window = nullptr;
	renderer = nullptr;
}

const bool Game::isFinished() const {
	return finished;
}
void Game::run(){
	init();
	while (!finished) {
		frameStart = SDL_GetTicks();
		handleEvents();
		update();
		render();
		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}
	clean();
}

Game::~Game() {
}
void Game::init() {
	p1Score = p2Score = 0;
	p1Speed = p2Speed = 0;
	p1PosY = p2PosY = 240;
	p1PosX = 10;
	p2PosX = 630;
	ballSpeed = 0;
	playersMaxSpeed = 640/MAXFPS; //this is intended to be px/s
	srand(time(NULL));
	resetBall();
	boardWidth = 10;
	boardHeight = 50;
	ballWidth = 10;
	ballHeight = 10;
	finished = false;
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		throw std::exception("could not initialize SDL subsystems");
	}
	window = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}
void Game::update() {
	//update player positions
	p1PosY += p1Speed * playersMaxSpeed;
	if (p1PosY + boardHeight / 2 > 480) {		//reached bottom
		p1PosY = 480 - boardHeight / 2;
	}
	else if (p1PosY - boardHeight / 2 < 0) {	//reached top
		p1PosY = boardHeight / 2;
	}
	
	p2PosY += p2Speed * playersMaxSpeed;
	if (p2PosY + boardHeight / 2 > 480) {		//reached bottom
		p2PosY = 480 - boardHeight / 2;
	}
	else if (p2PosY - boardHeight / 2 < 0) {	//reached top
		p2PosY = boardHeight / 2;
	}

	//update ball position
	ballPosX += ballSpeed * cos(ballAngle*M_PI / 180);
	ballPosY += ballSpeed * sin(ballAngle*M_PI / 180);
	
	//check for colisions
	if (ballPosY - ballHeight / 2 <= 0) {		//reached top
		ballPosY = ballHeight / 2;
		ballAngle =-ballAngle;
	}
	else if (ballPosY + ballHeight / 2 > 480) { //reached bottom
		ballPosY = 480 - ballHeight / 2;
		ballAngle =-ballAngle;
	}
	if (ballPosX - ballWidth / 2 <= 0) {
		p2Score++;
		resetBall();
		std::cout << "Score: " << p1Score << " - " << p2Score << std::endl;
	}
	else if (ballPosX + ballWidth / 2 >= 640) {
		p1Score++;
		resetBall();
		std::cout << "Score: " << p1Score << " - " << p2Score << std::endl;
	}
	else if ((ballPosX - p1PosX < (ballWidth + boardWidth) / 2) && (abs(ballPosY - p1PosY) < (ballHeight + boardHeight) / 2)) {
		ballAngle = 180 - ballAngle;
		ballPosX = ceil(p1PosX + (ballWidth + boardWidth) / 2);
	}
	else if (( p2PosX - ballPosX < (ballWidth + boardWidth) / 2) && (abs(ballPosY - p2PosY) < (ballHeight + boardHeight) / 2)) {
		ballAngle = 180 - ballAngle;
		ballPosX = floor(p2PosX - (ballWidth + boardWidth) / 2)-1;
	}
	if (ballAngle > 360) ballAngle -= 360;
	if (ballAngle < 0) ballAngle += 360;
}

void Game::render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	p1Rect.x = p1PosX - boardWidth / 2;
	p1Rect.w = boardWidth;
	p1Rect.y = p1PosY - boardHeight / 2;
	p1Rect.h = boardHeight;

	p2Rect.x = p2PosX - boardWidth / 2;
	p2Rect.w = boardWidth;
	p2Rect.y = p2PosY - boardHeight / 2;
	p2Rect.h = boardHeight;

	ballRect.x = ballPosX - ballWidth / 2;
	ballRect.w = ballWidth;
	ballRect.y = ballPosY - ballHeight / 2;
	ballRect.h = ballHeight;

	SDL_RenderFillRect(renderer, &p1Rect);
	SDL_RenderFillRect(renderer, &p2Rect);
	SDL_RenderFillRect(renderer, &ballRect);

	SDL_RenderPresent(renderer);
}

void Game::handleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		finished = true;
		break;
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym) {
		case SDLK_w:
			p1Speed = -1;
			break;
		case SDLK_s:
			p1Speed = 1;
			break;
		case SDLK_i:
			p2Speed = -1;
			break;
		case SDLK_k:
			p2Speed = 1;
			break;
		}
		break;
	case SDL_KEYUP:
		switch (event.key.keysym.sym) {
		case SDLK_w:
			p1Speed = 0;
			break;
		case SDLK_s:
			p1Speed = 0;
			break;
		case SDLK_i:
			p2Speed = 0;
			break;
		case SDLK_k:
			p2Speed = 0;
			break;
		}
		break;
	}
}

void Game::clean() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Game::resetBall() {
	ballPosX = 320;
	ballPosY = 240;
	ballSpeed = 200 / MAXFPS;
	ballAngle = ((rand() % 4) * 90. + 45.);
}
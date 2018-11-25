#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include <stdexcept>
#include <iostream>

#include <SDL.h>

#include "game.h"
//#include "Wall.h"
//#include "GoalZone.h"

Game::Game() {
	ball = nullptr;
	p1 = nullptr;
	p2 = nullptr;
}

void Game::init() {
	GameMode::init();
	srand(time(NULL));
	p1Score = p2Score = 0;
	p1 = new Player(290, 215, SDLK_w, SDLK_s);
	p1->getComponent<SolidRendererComponent>().fillColor = { 255, 0, 0, 255 };
	registerEntity(p1);
	p2 = new Player(345, 215, SDLK_i, SDLK_k);
	p2->getComponent<SolidRendererComponent>().fillColor = { 0, 0, 255, 255 };
	registerEntity(p2);
	ball = new Ball(315, 235);
	registerEntity(ball);
	Wall * wall = new Wall(0, 0, 640, 10);
	wall->getComponent<SolidRendererComponent>().fillColor = { 150, 150, 150, 255 };
	registerEntity(wall);
	wall = new Wall(0, 470, 640, 480);
	wall->getComponent<SolidRendererComponent>().fillColor={ 150, 150, 150, 255 };
	registerEntity(wall);
	GoalZone * goal = new GoalZone(-10, 0, 0, 480);
	goal->getComponent<ColliderComponent>().addBinding([this](Entity *) {this->scoreGoal(2); });
	registerEntity(goal);
	goal = new GoalZone(640, 0, 650, 480);
	goal->getComponent<ColliderComponent>().addBinding([this](Entity *) {this->scoreGoal(1); });
	registerEntity(goal);
}

void Game::showScore() {
	std::cout << "Score: " << p1Score << " - " << p2Score << std::endl;
}

void Game::scoreGoal(int player){
	if (player == 1) p1Score++;
	if (player == 2) p2Score++;
	showScore();
	ball->resetSpeed();
}

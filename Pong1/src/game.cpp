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
	ball = new Ball(315, 235);
	auto ballSubs =ball->getComponent<ColliderComponent>().getSubscriberOnCollision();
	registerEntity(ball);

	p1 = new Player(290, 215, SDLK_w, SDLK_s);
	p1->getComponent<SolidRendererComponent>().fillColor = { 255, 0, 0, 255 };
	p1->getComponent<ColliderComponent>().getEventCollision()->subscribe(ballSubs);
	registerEntity(p1);

	p2 = new Player(345, 215, SDLK_i, SDLK_k);
	p2->getComponent<SolidRendererComponent>().fillColor = { 0, 0, 255, 255 };
	p2->getComponent<ColliderComponent>().getEventCollision()->subscribe(ballSubs);
	registerEntity(p2);
	
	Wall * wall = new Wall(0, 0, 640, 10);
	wall->getComponent<SolidRendererComponent>().fillColor = { 150, 150, 150, 255 };
	wall->getComponent<ColliderComponent>().getEventCollision()->subscribe(ballSubs);
	registerEntity(wall);

	wall = new Wall(0, 470, 640, 480);
	wall->getComponent<SolidRendererComponent>().fillColor={ 150, 150, 150, 255 };
	wall->getComponent<ColliderComponent>().getEventCollision()->subscribe(ballSubs);
	registerEntity(wall);

	GoalZone * goal = new GoalZone(-10, 0, 0, 480);
	goal->getComponent<ColliderComponent>().getEventCollision()->subscribe(ballSubs);
	goal->getComponent<ColliderComponent>().getSubscriberOnCollision()->rebind(
		[this](Entity * e){
			if (dynamic_cast<Ball*>(e) != nullptr) Game::scoreGoal(2);
		}
	);

	//goal->getComponent<ColliderComponent>().getEventOnCollision()->subscribe(Subscriber) addBinding([this](Entity *) {this->scoreGoal(2); });
	registerEntity(goal);
	
	goal = new GoalZone(640, 0, 650, 480);
	goal->getComponent<ColliderComponent>().getEventCollision()->subscribe(ballSubs);
	goal->getComponent<ColliderComponent>().getSubscriberOnCollision()->rebind(
		[this](Entity * e){
			if (dynamic_cast<Ball*>(e) != nullptr) Game::scoreGoal(1);
		}
	);
	//goal->getComponent<ColliderComponent>().addBinding([this](Entity *) {this->scoreGoal(1); });
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

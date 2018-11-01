#include "..\include\GameMode.h"
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include <stdexcept>
#include <iostream>

#include <SDL.h>
#include <vector>

GameMode::GameMode()
{
	window = nullptr;
	renderer = nullptr;
}


GameMode::~GameMode()
{
}

const bool GameMode::isFinished() const {
	return finished;
}

void GameMode::registerEntity(Entity * newEntityPtr){
	if (newEntityPtr != nullptr) entities.insert(newEntityPtr);
}

void GameMode::unregisterEntity(Entity * entityPtr){
	std::set<Entity *>::iterator iter=entities.find(entityPtr);
	if (iter!=entities.end()) {
		entities.erase(iter);
		delete entityPtr;
	}
}

void GameMode::init() {
	finished = false;
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		throw std::exception("could not initialize SDL subsystems");
	}
	window = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void GameMode::update() {
	for (Entity * entity : entities) {
		entity->update();
	}
	//this can be optimized...
	for (Entity * e1 : entities) {
		for (Entity * e2 : entities) {
			if (e1 != e2 && Entity::checkCollision(e1->getRect(), e2->getRect())) {
				e1->eventCollission(e2);
			}
		}
	}
}

void GameMode::render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	for (Entity * entity : entities) {
		entity->render(renderer);
	}
	SDL_RenderPresent(renderer);
}

void GameMode::handleEvent() {
	SDL_Event event;
	SDL_PollEvent(&event);
	if (event.type == SDL_QUIT) {
		finished = true;
		return;
	}
	for (Entity * entity : entities) {
		entity->handleEvent(event);
	}
}

void GameMode::clean() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void GameMode::unregisterAllEntities(){
	for (Entity* entityPtr : entities) {
		delete entityPtr;
	}
	entities.clear();
}

void GameMode::gameLoop() {
	init();
	while (!finished) {
		frameStart = SDL_GetTicks();
		handleEvent();
		update();
		render();
		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}
	clean();
}
#pragma once
#include <SDL.h>
#include <set>
#include "ECS.h"
class GameMode {
protected:
	//data for rendering
	SDL_Window * window;
	SDL_Renderer * renderer;
	SDL_Rect p1Rect, p2Rect, ballRect;
	const int MAXFPS = 60;
	const int frameDelay = 1000 / MAXFPS;
	Uint32 frameStart;
	int frameTime;
	bool finished;
	std::set<Entity *> entities;

protected:
	//protected methods for the game
	virtual void init();
	virtual void update();
	virtual void render();
	virtual void handleEvent();
	virtual void clean();
	virtual void unregisterAllEntities();

public:
	GameMode();
	~GameMode() = default;
	void gameLoop();
	const bool isFinished() const;
	void registerEntity(Entity * newEntity);
	void unregisterEntity(Entity * newEntity);
};


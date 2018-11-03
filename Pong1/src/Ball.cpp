#include "../include/Ball.h"
#include "../include/Player.h"
#include <stdlib.h>     /* srand, rand */


void Ball::update(){
	//update ball position
	posX += speed * cos(angle*M_PI / 180);
	posY += speed * sin(angle*M_PI / 180);

	//check for colisions on top or bottom to
	if (posY <= 0) {		//reached top
		posY = 0;
		angle = -angle;
	}
	else if (posY + height > 480) { //reached bottom
		posY = 480 - height;
		angle = -angle;
	}
	if (angle > 360) angle -= 360;
	if (angle < 0) angle += 360;
}

void Ball::render(SDL_Renderer * renderer){
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &this->getRect());
}

void Ball::resetSpeed(){
	posX = 320;
	posY = 240;
	speed = 200 / 60;
	angle = ((rand() % 4) * 90. + 45.);
}

Ball::Ball(float x, float y){
	posX = x;
	posY = y;
	width = 10;
	height = 10;
	speed = 0;
	angle = 0;
	resetSpeed();
}

void Ball::eventCollission(Entity * entityPtr){
	if (dynamic_cast<Player*>(entityPtr) != nullptr) {
		if (posX > entityPtr->getX()) {
			posX = entityPtr->getX() + entityPtr->getWidth();
		}
		else {
			posX = entityPtr->getX() - width;
		}
		angle = 180 - angle;
		if (angle > 360) angle -= 360;
		if (angle < 0) angle += 360;
	}
}

Ball::~Ball(){
}

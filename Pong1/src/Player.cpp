#include "../include/Player.h"

void Player::update() {
	//update player positions
	posY += speedFactor * maxSpeed;
	if (posY + height > 480) {		//reached bottom
		posY = 480 - height;
	}
	else if (posY < 0) {	//reached top
		posY = 0;
	}
}

void Player::render(SDL_Renderer * renderer) {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect rect = getRect();
	SDL_RenderFillRect(renderer, &rect);
}

void Player::handleEvent(const SDL_Event & event) {
	SDL_Keycode key;
	switch (event.type) {
	case SDL_KEYDOWN:
		key = event.key.keysym.sym;
		if (key == up) speedFactor = -1;
		else if (key == down) speedFactor = 1;
		break;
	case SDL_KEYUP:
		key = event.key.keysym.sym;
		if (key == up && speedFactor == -1) speedFactor = 0;
		else if (key == down && speedFactor == 1) speedFactor = 0;
		break;
	}
}

void Player::setInputEventUp(const SDL_Keycode up) {
	this->up = up;
}

void Player::setInputEventDown(const SDL_Keycode down) {
	this->down = down;
}

Player::Player(float x, float y, SDL_Keycode up, SDL_Keycode down):up(up), down(down){
	posX = x;
	posY = y;
	maxSpeed = 10;
	speedFactor = 0;
	height = 50;
	width = 10;
}
#include "../include/Player.h"
#include "../include/TransformComponent.h"
#include "../include/ColliderComponent.h"
#include "../include/SolidRendererComponent.h"
#include "../include/MovementComponent.h"

/*void Player::update() {
	//update player positions
	posY += speedFactor * maxSpeed;
	if (posY + height > 480) {		//reached bottom
		posY = 480 - height;
	}
	else if (posY < 0) {	//reached top
		posY = 0;
	}
}
*/

/*void Player::handleEvent(const SDL_Event & event) {
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
*/
void Player::setInputEventUp(const SDL_Keycode up) {
	this->up = up;
}

void Player::setInputEventDown(const SDL_Keycode down) {
	this->down = down;
}

Player::Player(float x, float y, SDL_Keycode up, SDL_Keycode down):up(up), down(down){
	SDL_Rect auxRect;
	SDL_Color color;
	auxRect.x = 0;
	auxRect.y = 0;
	auxRect.w = 10;
	auxRect.h = 50;
	color.r = color.g = color.b = color.a = 255;
	addComponent<TransformComponent>(x,y);
	addComponent<MovementComponent>(10);
	addComponent<ColliderComponent>(auxRect);
	addComponent<SolidRendererComponent>(color, auxRect);
}
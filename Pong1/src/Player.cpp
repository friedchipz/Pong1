#include "Player.h"
#include "TransformComponent.h"
#include "ColliderComponent.h"
#include "SolidRendererComponent.h"
#include "MovementComponent.h"


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
	addComponent<TransformComponent>(x,y);
	addComponent<MovementComponent>(10);
	addComponent<ColliderComponent>(SDL_Rect { 0, 0, 10, 50 });
	addComponent<SolidRendererComponent>(SDL_Color { 255, 255, 255,255 }, SDL_Rect { 0, 0, 10, 50 });
}
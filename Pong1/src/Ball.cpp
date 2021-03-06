#include <stdlib.h>     /* srand, rand */

#include "Ball.h"
#include "Player.h"
#include "CoreComponents.h"

void Ball::resetSpeed() {
	getComponent<TransformComponent>().pos = Vector2d(320,240);
	getComponent<PolarMovementComponent>().speed = getComponent<PolarMovementComponent>().maxSpeed;
	getComponent<PolarMovementComponent>().angle = ((rand() % 4) * 90. + 45.);
}

Ball::Ball(float x, float y) {
	SDL_Color color;
	color = { 255, 255, 255, 255 };
	this->addComponent<TransformComponent>(x, y);
	this->addComponent<PolarMovementComponent>(200/60);
	this->addComponent<ColliderComponent>(SDL_Rect {0,0,10,10});
	this->addComponent<SolidRendererComponent>(color, SDL_Rect{ 0,0,10,10 });
	getComponent<ColliderComponent>().getSubscriberOnCollision()->rebind(
		[this](Entity* e){actOnCollision(e);}
	);
	resetSpeed();
}

void Ball::actOnCollision(Entity * entityPtr) {
	if (entityPtr->hasComponent<ColliderComponent>()) {
		SDL_Rect oppositeRect = entityPtr->getComponent<ColliderComponent>().getTransformedArea();
		SDL_Rect ownRect = getComponent<ColliderComponent>().getTransformedArea();
		if (ColliderComponent::fromRight(oppositeRect, ownRect)) {
			getComponent<PolarMovementComponent>().bounceH();
			getComponent<TransformComponent>().x = oppositeRect.x + oppositeRect.w;
		} else
		if (ColliderComponent::fromLeft(oppositeRect, ownRect)) {
			getComponent<PolarMovementComponent>().bounceH();
			getComponent<TransformComponent>().x = oppositeRect.x - ownRect.w;
		}
		if (ColliderComponent::fromBelow(oppositeRect, ownRect)) {
			getComponent<PolarMovementComponent>().bounceV();
			getComponent<TransformComponent>().y = oppositeRect.y + oppositeRect.h;
		} else
		if (ColliderComponent::fromAbove(oppositeRect, ownRect)) {
			getComponent<PolarMovementComponent>().bounceV();
			getComponent<TransformComponent>().y = oppositeRect.y - ownRect.h;
		}
	}
}

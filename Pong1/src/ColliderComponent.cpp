#include "CoreComponents.h"

ColliderComponent::ColliderComponent(SDL_Rect area){
	this->area = area;
	eventCollision = Singleton<EventSystem>::getInstance()->newEvent<Entity*>();
	onCollision = new Subscriber<Entity*>();
}

ColliderComponent::ColliderComponent(Vector2d pos, Vector2d size) :
	ColliderComponent(SDL_Rect{ (int)pos.x, (int)pos.y, (int)size.x, (int)size.y }) {}

ColliderComponent::~ColliderComponent(){
	delete eventCollision;
	delete onCollision;
}

SDL_Rect ColliderComponent::getTransformedArea() const{
	return entity->getComponent<TransformComponent>().transformRect(area);
}

Event<Entity *> * ColliderComponent::getEventCollision() const{
	return eventCollision;
}

Subscriber<Entity *> * ColliderComponent::getSubscriberOnCollision() const{
	return onCollision;
}

bool operator<(std::function<void(Entity*)> const & f1, std::function<void(Entity*)> const  & f2) {
	return &f1 < &f2;
}

void ColliderComponent::collide(Entity * triggerer){
	(*eventCollision)(triggerer);
}

bool ColliderComponent::fromAbove(SDL_Rect ref, SDL_Rect body){
	return body.y < ref.y && ref.y < body.y + body.h;
}

bool ColliderComponent::fromBelow(SDL_Rect ref, SDL_Rect body){
	return body.y < ref.y + ref.h  && ref.y +ref.h < body.y +body.h;
}

bool ColliderComponent::fromLeft(SDL_Rect ref, SDL_Rect body) {
	return body.x < ref.x && ref.x < body.x + body.w;
}

bool ColliderComponent::fromRight(SDL_Rect ref, SDL_Rect body) {
	return body.x < ref.x + ref.w  && ref.x + ref.w < body.x + body.w;
}

bool ColliderComponent::checkCollission(ColliderComponent & checked) {
	SDL_Rect oppositeArea = checked.getTransformedArea();
	SDL_Rect ownArea = this->getTransformedArea();
	if (ownArea.x + ownArea.w > oppositeArea.x &&
		oppositeArea.x + oppositeArea.w > ownArea.x &&
		ownArea.y + ownArea.h > oppositeArea.y &&
		oppositeArea.y + oppositeArea.h > ownArea.y)
	{
		return true;
	}
	return false;
}

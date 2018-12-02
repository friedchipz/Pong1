#include "CoreComponents.h"

ColliderComponent::ColliderComponent(SDL_Rect area){
	this->area = area;
}

ColliderComponent::ColliderComponent(Vector2d pos, Vector2d size) :
	ColliderComponent(SDL_Rect{ (int)pos.x, (int)pos.y, (int)size.x, (int)size.y }) {}

SDL_Rect ColliderComponent::getTransformedArea(){
	return entity->getComponent<TransformComponent>().transformRect(area);
}

void ColliderComponent::addBinding(std::function<void(Entity*)> const callback){
	std::function<void(Entity*)> f = callback;
	//callBacks.push_back(callback);
	callBacks.insert(callBacks.end(), callback);
}

void ColliderComponent::delBinding(std::function<void(Entity*)> callback) {
	//std::unordered_set<std::function<void(Entity*)>>::iterator bindIter = callBacks.find(callback);
	auto bindIter = callBacks.find(callback);
	if (bindIter!=callBacks.end())
	callBacks.erase(bindIter);
	//callBacks.remove(callback);
}

bool operator<(std::function<void(Entity*)> const & f1, std::function<void(Entity*)> const  & f2) {
	return &f1 < &f2;
}

void ColliderComponent::collide(Entity * triggerer){
	for (auto callback : callBacks) {
		callback(triggerer);
	}
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

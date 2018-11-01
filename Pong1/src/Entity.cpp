#include "..\include\Entity.h"



Entity::Entity()
{
}


Entity::~Entity()
{
}

const float Entity::getX() const
{
	return posX;
}

const float Entity::getY() const
{
	return posY;
}

const float Entity::getWidth() const
{
	return width;
}

const float Entity::getHeight() const
{
	return height;
}

const SDL_Rect Entity::getRect() const
{
	SDL_Rect rect;
	rect.x = posX;
	rect.y = posY;
	rect.w = width;
	rect.h = height;
	return rect;
}

void Entity::eventCollission(Entity * entityPtr)
{
}

bool Entity::checkCollision(SDL_Rect r1, SDL_Rect r2){
	if (r1.x + r1.w > r2.x &&
		r2.x + r2.w > r1.x &&
		r1.y + r1.h > r2.y &&
		r2.y + r2.h > r1.y)
	{
		return true;
	}
	return false;
}

void Entity::update() {
}

void Entity::render(SDL_Renderer * renderer) {

}

void Entity::handleEvent(const SDL_Event & event)
{
}

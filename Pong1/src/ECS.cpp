#include "ECS.h"

Entity::Entity() {
	components.resize(MAXCOMPONENTS, nullptr);
}

Entity::~Entity() {
	for (Component * component : components) {
		if (component != nullptr) delete component;
	}
}

void Entity::update() {
	for (Component * component : components) {
		if (component != nullptr) component->update();
	}
}

void Entity::render(SDL_Renderer * renderer) {
	for (Component * component : components) {
		if (component != nullptr) component->render(renderer);
	}
}

void Component::render(SDL_Renderer * renderer) {}
void Component::update(){}
void Component::init(){};
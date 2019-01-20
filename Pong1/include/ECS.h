#pragma once
#include <memory>
#include <vector>
#include <SDL.h>

#ifndef MAXCOMPONENTS
	#define MAXCOMPONENTS 32
#endif



class Component;
class Entity;

using ComponentID = std::size_t;

inline ComponentID getNewID() {
	static ComponentID lastID = 0;
	return lastID++;
}

template <typename T> inline ComponentID getComponentID() noexcept {
	static ComponentID typeID = getNewID();
	return typeID;
}

class Component {
public:
	Entity * entity;
public:
	virtual void init() {};
	virtual void update() {};
	virtual void render(SDL_Renderer * renderer) {};
	virtual ~Component() = default;
};

class Entity {
private:
	std::vector<Component*> components;
public:
	virtual void update();
	virtual void render(SDL_Renderer * renderer);
public:
	Entity();
	virtual ~Entity();
	template <typename T> inline bool hasComponent() {
		return components[getComponentID<T>()] != nullptr;
	}
	template <typename T> inline T& getComponent() {
		return *static_cast<T*>(components[getComponentID<T>()]);
	}
	template <typename T, typename... Args> inline T& addComponent(Args&&... mArgs) {
		T* component(new T(std::forward<Args>(mArgs)...));
		component->entity = this;
		component->init();
		components[getComponentID<T>()] = component;
		return *component;
	}
};


#pragma once
#include <functional>
#include <map>
#include <SDL.h>
#include "../include/ECS.h"
class InputComponent : public Component {
protected:
	std::map<SDL_Keycode ,std::function<void(float)>> callBacks;
public:
	void bind(SDL_Keycode);
	InputComponent();
	~InputComponent();
};


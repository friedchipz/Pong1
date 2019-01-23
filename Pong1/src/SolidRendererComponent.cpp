#include "SolidRendererComponent.h"

SolidRendererComponent::SolidRendererComponent(SDL_Color fillColor, SDL_Rect area): fillColor(fillColor), area(area){}

void SolidRendererComponent::render(SDL_Renderer * renderer){
	SDL_Rect renderArea;
	renderArea.x = area.x + entity->getComponent<TransformComponent>().pos.x;
	renderArea.y = area.y + entity->getComponent<TransformComponent>().pos.y;
	renderArea.w = area.w * entity->getComponent<TransformComponent>().scale.x;
	renderArea.h = area.h * entity->getComponent<TransformComponent>().scale.y;
	Uint8 r, g, b, a;
	SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);
	SDL_SetRenderDrawColor(renderer, fillColor.r, fillColor.g, fillColor.b, fillColor.a);
	SDL_RenderFillRect(renderer, &renderArea);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

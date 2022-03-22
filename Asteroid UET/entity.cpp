#include "player.h"
#include <SDL.h>
#include <SDL_image.h>
#include "entity.h"
#include<iostream>
Entity::Entity( SDL_Texture* p_tex)
	
{
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = 64;
	currentFrame.h = 64;
	tex = p_tex;
	//get currenrframe equal source image
	SDL_QueryTexture(p_tex, NULL, NULL, &currentFrame.w, &currentFrame.h);
}
SDL_Rect Entity::getCurrentFrame()
{
	return currentFrame;
}
//void Entity::setRect(SDL_Rect& cn) {
	//currentFrame = cn;
//}

void Entity::move(SDL_Event events,float& x,float& y){
	switch (events.key.keysym.sym)
	{
	case SDLK_UP:
		y = y - 10;
		std::cout << "con chim non";
		break;
	case SDLK_DOWN:
		y = y + 10;
		break;
	case SDLK_LEFT:
		x = x - 10;
		break;
	case SDLK_RIGHT:
		x = x + 10;
		break;
	}
}

SDL_Texture* Entity::getTex()
{	
	return tex;
}




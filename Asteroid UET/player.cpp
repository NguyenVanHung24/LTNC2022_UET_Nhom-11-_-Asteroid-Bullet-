#include "player.h"
#include <SDL.h>
#include <SDL_image.h>

Entity::Entity(float x,float y, SDL_Texture* p_tex)
	
{
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = 32;
	currentFrame.h = 32;
	SDL_QueryTexture(p_tex, NULL, NULL, &currentFrame.w, &currentFrame.h);
}

SDL_Texture* Entity::getTex()
{
	return tex;
}




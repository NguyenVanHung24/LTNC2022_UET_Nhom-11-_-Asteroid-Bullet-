#include "player.h"
#include <SDL.h>
#include <SDL_image.h>

Entity::Entity( SDL_Texture* p_tex)
	
{
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = 64;
	currentFrame.h = 64;
	tex = p_tex;
	SDL_QueryTexture(p_tex, NULL, NULL, &currentFrame.w, &currentFrame.h);
}
SDL_Rect Entity::getCurrentFrame()
{
	return currentFrame;
}


SDL_Texture* Entity::getTex()
{	
	return tex;
}




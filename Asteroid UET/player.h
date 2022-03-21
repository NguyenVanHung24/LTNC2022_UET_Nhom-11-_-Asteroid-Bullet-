#pragma once
#include <SDL.h>
#include <SDL_image.h>



class Entity
{
public:
	Entity(float x,float y, SDL_Texture* p_tex);
	SDL_Texture* getTex();
	
	
private:
	
	SDL_Rect currentFrame;
	SDL_Texture* tex;
};
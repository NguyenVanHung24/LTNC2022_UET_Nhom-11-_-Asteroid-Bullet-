#pragma once
#include <SDL.h>
#include <SDL_image.h>


class Entity{
public:
	Entity(SDL_Texture* p_tex);
	SDL_Texture* getTex();
	SDL_Rect getCurrentFrame();
private:
	
	SDL_Rect currentFrame;
	SDL_Texture* tex;
};
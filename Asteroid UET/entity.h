#ifndef ENTITY_H
#define ENTITY_H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

class Entity{
public:
	Entity();
	Entity(SDL_Texture* p_tex);
	SDL_Texture* getTex();
	SDL_Rect getCurrentFrame();
	//void setRect(SDL_Rect& cn);
	
protected:
	
	SDL_Rect currentFrame;
	SDL_Texture* tex;
}; 

#endif

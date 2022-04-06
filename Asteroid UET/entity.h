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
	int height, width;
	void getSize(SDL_Texture* t);
	SDL_Rect getRect();
protected:
	
	
	SDL_Texture* tex;
}; 

#endif

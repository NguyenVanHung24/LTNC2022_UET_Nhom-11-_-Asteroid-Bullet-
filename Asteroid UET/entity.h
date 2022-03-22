#pragma once
#include <SDL.h>
#include <SDL_image.h>


class Entity{
public:
	Entity(SDL_Texture* p_tex);
	SDL_Texture* getTex();
	SDL_Rect getCurrentFrame();
	//void setRect(SDL_Rect& cn);
	void move(SDL_Event event, float & x,float & y) ;
private:
	
	SDL_Rect currentFrame;
	SDL_Texture* tex;
};
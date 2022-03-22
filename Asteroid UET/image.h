#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "player.h"
#include "entity.h"

class RenderWindow
{
public:
	RenderWindow(const char* p_title, int p_w, int p_h);
	SDL_Texture* loadTexture(const char* p_filePath);
	void cleanUp();
	void clear();
	void render(SDL_Texture* p_tex);
	void render(Entity& p_entity, float x,float y);
	void render(float x,float y, SDL_Texture* p_tex);
	
	
	void display();
	SDL_Renderer* getRender();
private: SDL_Window* window;
	 SDL_Renderer* renderer;
	
};
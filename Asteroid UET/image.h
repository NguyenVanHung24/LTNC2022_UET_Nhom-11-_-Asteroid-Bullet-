#ifndef IMAGE_H
#define IMAGE_H
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "entity.h"
#include "bullet.h"
#include <iostream>

class RenderWindow{	
public: 
	RenderWindow(const char* p_title, int p_w, int p_h);
	SDL_Texture* loadTexture(const char* p_filePath);
	void cleanUp();
	void clear();
	void render(SDL_Texture* p_tex);
	void render(Entity& p_entity, float x,float y);
	void render(float x,float y, SDL_Texture* p_tex);
	void rendertext(const char* string, int size,int x,int y,SDL_Rect & rect);
	void renderExplosion(int x, int y, SDL_Rect* clip, SDL_Texture* p_tex);
	void drawlink(float x1, float y1, float x2, float y2);

	void handleEvent(SDL_Event event, int& start ,SDL_Rect rect[]);
	SDL_Renderer* getRender();
	void display();
	
	SDL_Window* window;
	SDL_Renderer* renderer;
	
};
#endif
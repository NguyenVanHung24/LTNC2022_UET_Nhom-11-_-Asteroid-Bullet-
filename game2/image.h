#ifndef IMAGE_H
#define IMAGE_H

#include "MainLib.h"
#include "entity.h"
#include "bullet.h"

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
	void rendertext(const char* string, int size, int x, int y);
	SDL_Texture* loadTextureFromText(std::string textureText, int x, int y, int size);
	SDL_Texture* loadTextureFromText(std::string textureText, int x, int y, int size, SDL_Rect& rect);
	void renderExplosion(int x, int y, SDL_Rect* clip, SDL_Texture* p_tex);
	void renderSmallExplosion(int x, int y, SDL_Rect* clip, SDL_Texture* p_tex);
	void renderPortion(int x, int y, int size_x, int size_y, SDL_Rect* button, SDL_Texture* p_tex, SDL_Rect &rect);
	void drawlink(float x1, float y1, float x2, float y2);
	void changeColor(Uint8 x,Uint8 y,Uint8 z);
	void handleEvent(SDL_Event event, int& start ,SDL_Rect rect[], int& pause);
	void handleState(SDL_Event event, int& state, SDL_Rect rect, SDL_Window* window);
	void handleQuit(SDL_Event event, int& start, SDL_Rect rect, SDL_Window* window);
	SDL_Renderer* getRender();
	void display();
	
	SDL_Window* window; 
	SDL_Renderer* renderer;
	SDL_Color textColor = { 255, 255, 255 };
	TTF_Font* gFont =TTF_OpenFont("font/Koulen-Regular.ttf", 60);
};
#endif
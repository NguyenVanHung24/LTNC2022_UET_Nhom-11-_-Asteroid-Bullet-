#pragma once
#include "image.h"

int MouseX=0, MouseY=0;
bool CheckInside(SDL_Rect Button, int x, int y) {
	if (x < Button.x) return false;
	if (x > Button.x + Button.w) return false;
	if (y < Button.y) return false;
	if (y > Button.y + Button.h) return false;
	return true;
}
//create window
RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h)
	:window(NULL), renderer(NULL)
{
	window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);

	if (window == NULL)
	{
		std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}
//load texture
SDL_Texture* RenderWindow::loadTexture(const char* p_filePath)
{
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer, p_filePath);

	if (texture == NULL)
		std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;

	return texture;
}

void RenderWindow::cleanUp()
{
	SDL_DestroyWindow(window);
}

void RenderWindow::clear()
{
	SDL_RenderClear(renderer);
}
//render full window
void RenderWindow::render(SDL_Texture* p_tex) {
	SDL_RenderCopy(renderer, p_tex, NULL, NULL);
}
//render with entity
void RenderWindow::render(Entity& p_entity, float x, float y)
{
	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	src.w;
	src.h;

	SDL_QueryTexture(p_entity.getTex(), NULL, NULL, &src.w, &src.h);

	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = src.w;
	dst.h = src.h;

	//std::cout << "skt";
	SDL_RenderCopy(renderer, p_entity.getTex(), &src, &dst);
}

void RenderWindow::renderExplosion(int x, int y, SDL_Rect* clip, SDL_Texture* p_tex)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, 200, 200 };

	//Render to screen
	SDL_RenderCopy(renderer, p_tex, clip, &renderQuad);
}

void RenderWindow::renderPortion(int x, int y, int size_x, int size_y, SDL_Rect* clip, SDL_Texture* p_tex, SDL_Rect &rect)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, size_x, size_y };
	rect = renderQuad;

	//Render to screen
	SDL_RenderCopy(renderer, p_tex, clip, &renderQuad);
}

//render with texture
void RenderWindow::render(float x,float y, SDL_Texture* p_tex)
{
	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	src.w;
	src.h;

	SDL_QueryTexture(p_tex, NULL, NULL, &src.w, &src.h);

	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = src.w;
	dst.h = src.h;

	SDL_RenderCopy(renderer, p_tex, &src, &dst);
}

void RenderWindow::rendertext(const char* string, int size,int x,int y, SDL_Rect& rect) {
	
	gFont = TTF_OpenFont("D:/Asteroid UET/font/Koulen-Regular.ttf", size);
	if (gFont == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		//Render text
		
		SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, string, textColor);
		if (textSurface == NULL)
		{
			printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
		}
		else 
		{
			//Create texture from surface pixels
			SDL_Texture* Texture = SDL_CreateTextureFromSurface(renderer, textSurface);
			if (Texture == NULL)
			{
				printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
			}
			SDL_Rect src;
			src.x = 0;
			src.y = 0;
			src.w;
			src.h;

			SDL_QueryTexture(Texture, NULL, NULL, &src.w, &src.h);

			SDL_Rect dst;
			dst.x = x;
			dst.y = y;
			dst.w = src.w;
			dst.h = src.h;
			rect = dst;
			//Get rid of old surface
			SDL_FreeSurface(textSurface);
			
			SDL_RenderCopy(renderer, Texture, &src, &dst);
			SDL_DestroyTexture(Texture);
			Texture = NULL;
		}

		
	}
}
void RenderWindow::rendertext(const char* string, int size, int x, int y) {
	
	gFont = TTF_OpenFont("D:/Asteroid UET/font/Koulen-Regular.ttf", size);
	if (gFont == NULL)
	{
		std::cout << "Failed to load lazy font! SDL_ttf Error: ", TTF_GetError();
	}
	else
	{
		//Render text
		SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, string, textColor);
		if (textSurface == NULL)
		{
			std::cout << "Unable to render text surface! SDL_ttf Error:" << TTF_GetError();
		}
		else
		{
			//Create texture from surface pixels
			SDL_Texture* Texture = SDL_CreateTextureFromSurface(renderer, textSurface);
			if (Texture == NULL)
			{
				std::cout << "Unable to create texture from rendered text! SDL Error:" << SDL_GetError();
			}
			SDL_Rect src;
			src.x = 0;
			src.y = 0;
			src.w;
			src.h;
			SDL_QueryTexture(Texture, NULL, NULL, &src.w, &src.h);
			SDL_Rect dst;
			dst.x = x;
			dst.y = y;
			dst.w = src.w;
			dst.h = src.h;
			//Get rid of old surface
			SDL_FreeSurface(textSurface);

			SDL_RenderCopy(renderer, Texture, &src, &dst);
			SDL_DestroyTexture(Texture);
			Texture = NULL;
		}


	}
}
SDL_Texture* RenderWindow::loadTextureFromText(std::string textureText, int x, int y, int size,SDL_Rect &rect) {

	gFont = TTF_OpenFont("D:/Asteroid UET/font/Koulen-Regular.ttf", size);
	SDL_Surface* loadedText = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, loadedText);
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = loadedText->w;
	dst.h = loadedText->h;

	rect = dst;
	SDL_FreeSurface(loadedText);
	loadedText = nullptr;
	return texture;
}
SDL_Texture* RenderWindow::loadTextureFromText(std::string textureText, int x , int y, int size ) {

	gFont = TTF_OpenFont("D:/Asteroid UET/font/Koulen-Regular.ttf", size);
	SDL_Surface* loadedText = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, loadedText);
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = loadedText->w;
	dst.h = loadedText->h;


	SDL_FreeSurface(loadedText);
	loadedText = nullptr;
	return texture;
}


void RenderWindow::changeColor(Uint8 x,Uint8 y,Uint8 z) {
	textColor = { x,y,z };
};

void RenderWindow::handleEvent(SDL_Event event, int& start, SDL_Rect rect[]) {
	if (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP) {
		SDL_GetMouseState(&MouseX, &MouseY);
		
	}
	for (int i = 0; i < 5; i++) {
		if (CheckInside(rect[i], MouseX, MouseY))
			switch (i)
			{
			case 0:
				switch (event.type)
				{
				case SDL_MOUSEMOTION:
					//changeColor(250, 250, 250);
					break;
				case SDL_MOUSEBUTTONDOWN:
					start = 0;
					break;
				case SDL_MOUSEBUTTONUP:
					changeColor(255, 255, 255);
					break;
				}
				break;
			case 1:
				switch (event.type)
				{
				case SDL_MOUSEMOTION:
					//changeColor(250, 250, 250);
					break;
				case SDL_MOUSEBUTTONDOWN:
					start = 1;
					break;
				case SDL_MOUSEBUTTONUP:
					changeColor(255, 255, 255);
					break;
				}
				break;
			case 2:
				switch (event.type)
				{
				case SDL_MOUSEMOTION:
					//changeColor(250, 250, 250);
					break;
				case SDL_MOUSEBUTTONDOWN:
					start = 2;
					break;
				case SDL_MOUSEBUTTONUP:
					changeColor(255, 255, 255);
					break;
				}
				break;
			case 3:
				switch (event.type)
				{
				case SDL_MOUSEMOTION:
					//changeColor(250, 250, 250);
					break;
				case SDL_MOUSEBUTTONDOWN:
					start = 3;
					break;
				case SDL_MOUSEBUTTONUP:
					changeColor(255, 255, 255);
					break;
				}
				break;
			case 4:
				switch (event.type)
				{
				case SDL_MOUSEMOTION:
					//changeColor(250, 250, 250);
					break;
				case SDL_MOUSEBUTTONDOWN:
					start = 4;
					break;
				case SDL_MOUSEBUTTONUP:
					changeColor(255, 255, 255);
					break;
				}
				break;
			default:
				break;
			}

		
	}
}

void RenderWindow::handleState(SDL_Event event, bool& state, SDL_Rect rect, SDL_Window* window) {
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		SDL_GetMouseState(&MouseX, &MouseY);
	}
	if (CheckInside(rect, MouseX, MouseY)) {
		if (event.type == SDL_MOUSEBUTTONUP) {
			if (state == true) {
				state = false;
			}
			else {
				state = true;
			}
		}
	}
}

void RenderWindow::display()
{
	SDL_RenderPresent(renderer);
}
SDL_Renderer* RenderWindow::getRender() {
	return renderer;
}

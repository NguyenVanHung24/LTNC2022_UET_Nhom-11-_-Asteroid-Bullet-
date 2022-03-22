#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "image.h"
#include "player.h"
#include "entity.h"




int main(int argc, char* args[])
{
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
		std::cout << "HEY.. SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;

	if (!(IMG_Init(IMG_INIT_PNG)))
		std::cout << "IMG_init has failed. Error: " << SDL_GetError() << std::endl;

	RenderWindow window("GAME v1.0", 1280, 720);

	SDL_Texture* background = window.loadTexture("D:/Asteroid UET/image/background.png");
	
	SDL_Texture* player= window.loadTexture("D:/Asteroid UET/image/player.png");
	SDL_Texture* bullet = window.loadTexture("D:/Asteroid UET/image/alienBullet.png");

	Entity object(player);
	if (object.getTex() == NULL) std::cout << "con chim non1";
	bool gameRunning = true;

	SDL_Event event;
	int n=0; float x = 100; float y = 500;
	while (gameRunning)
	{
		// Get our controls and events
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				gameRunning = false;
			
			object.move(event, x, y);
			
			std::cout << x << y;
			
		}
		window.clear();

		
		
		window.render(background);
		window.render(object, 150, 160);
		window.render(object,x,y);
		window.render(120, 500, player);
		window.display();
		
	}

	window.cleanUp();
	SDL_Quit();

	return 0;
}
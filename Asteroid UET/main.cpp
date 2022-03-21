#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "image.h"
#include "player.h"





int main(int argc, char* args[])
{
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
		std::cout << "HEY.. SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;

	if (!(IMG_Init(IMG_INIT_PNG)))
		std::cout << "IMG_init has failed. Error: " << SDL_GetError() << std::endl;

	RenderWindow window("GAME v1.0", 1280, 720);

	SDL_Texture* background = window.loadTexture("D:/Asteroid UET/image/background.png");
	
	SDL_Texture* player=window.loadTexture("D:/Asteroid UET/image/player.png");

	bool gameRunning = true;

	SDL_Event event;
	int n=0; int x = 0; int y = 0;
	while (gameRunning)
	{
		// Get our controls and events
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				gameRunning = false;
		}

		window.clear();
		window.render(background);
		
		
		window.render(100,100,player);

		window.display();
		std::cout<<n;
		n++;
	}

	window.cleanUp();
	SDL_Quit();

	return 0;
}
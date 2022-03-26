#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "image.h"
#include "player.h"
#include "entity.h"
#include "bullet.h"
#include <vector>
using namespace std;
static SDL_Window* window;
static SDL_Renderer* renderer;
int main(int argc, char* args[])
{
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
		std::cout << "HEY.. SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;

	if (!(IMG_Init(IMG_INIT_PNG)))
		std::cout << "IMG_init has failed. Error: " << SDL_GetError() << std::endl;

	RenderWindow window("GAME v1.0", 1280, 720);

	SDL_Texture* background = window.loadTexture("D:/Asteroid UET/image/background.png");
	
	SDL_Texture* pilot= window.loadTexture("D:/Asteroid UET/image/player.png");
	SDL_Texture* pow = window.loadTexture("D:/Asteroid UET/image/alienBullet.png");
	player player(pilot);
	
	bullet bull(pow);	
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
			
			
			player.move(event, player.x_pos, player.y_pos);
			for (int i = 0; i < player.count; i++)
				player.get_bullet().push_back(bull);
		}
		window.clear();
		window.render(background);
		
		
		
		window.render(player, player.getX(), player.getY());
		window.render(bull,bull.x_pos ,bull.y_pos );

		vector<bullet> bangdan = player.get_bullet();
		for (int i = 0; i < player.count; i++)
		{
			bullet dan = bangdan[i];
			window.render(dan, dan.x_pos, dan.y_pos);
		}
		
		window.display();
		
	}

	window.cleanUp();
	SDL_Quit();

	return 0;
}
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "image.h"
#include "player.h"
#include "entity.h"
#include "bullet.h"
#include <vector>
using namespace std;

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
	
	bullet p_bull(pow,player.getX(),player.getY());
	vector<bullet> bullet_list;
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
			
			
			player.move(event, player.x_pos, player.y_pos,player.gun);
			//make bullet
			if (player.gun == true) {
				p_bull.x_pos = player.x_pos+36;
				p_bull.y_pos = player.y_pos+18;
				bullet_list.push_back(p_bull);
				player.gun = false;
			}
			
		}
		window.clear();
		window.render(background);
		
		
		
		window.render(player, player.getX(), player.getY());
		//window.render(p_bull,p_bull.x_pos ,p_bull.y_pos );
		//render bullet
		for (int i = 0; i < bullet_list.size(); i++) {
			bullet& bull = bullet_list[i];
			bull.x_pos = bull.x_pos + 1;
			window.render(bull, bull.x_pos, bull.y_pos);

		}
		//DRAW LINE
		//window.drawlink(player.x_pos+24, player.y_pos+24, bull.x_pos, bull.y_pos);
		
		window.display();
		
	}

	window.cleanUp();
	SDL_Quit();

	return 0;
}
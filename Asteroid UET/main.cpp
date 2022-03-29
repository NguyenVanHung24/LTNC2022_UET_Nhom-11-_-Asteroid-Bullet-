#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <ctime>
#include "image.h"
#include "player.h"
#include "entity.h"
#include "enemy.h"
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
	
	
	//get texture
	SDL_Texture* background = window.loadTexture("D:/Asteroid UET/image/background.png");
	SDL_Texture* pilot= window.loadTexture("D:/Asteroid UET/image/player.png");
	SDL_Texture* pow = window.loadTexture("D:/Asteroid UET/image/alienBullet.png");
	SDL_Texture*  p_enemy= window.loadTexture("D:/Asteroid UET/image/enemy.png");
	
	
	
	//init object
	player player(pilot);
	enemy Enemy(p_enemy);
	bullet p_bull(pow,player.getX(),player.getY());
	vector <bullet> bullet_list;
	vector <enemy> enemy_team;

	bool gameRunning = true;
	
	//init enemy
	for (int i = 0; i < 4; i++) {
		enemy_team.push_back(Enemy);
		enemy_team[i].y_pos= rand()%720+i*145;
		if (enemy_team[i].y_pos > 720) enemy_team[i].y_pos *= 0.2;
		enemy_team[i].x_pos = 1208 + i * 190;
	}
	SDL_Event event;
	
	while (gameRunning)
	{
		// Get our controls and events
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				gameRunning = false;


			player.move(event, player.x_pos, player.y_pos, player.gun);
			//make bullet for player
			if (player.gun == true) {
				p_bull.x_pos = player.x_pos + 36;
				p_bull.y_pos = player.y_pos + 18;
				bullet_list.push_back(p_bull);
				player.gun = false;

			}

		}
		window.clear();
		window.render(background);
		//render enemy team and bull
		for (int i = 0; i < 4; i++) {
			enemy& _enemy = enemy_team[i];
			window.render(_enemy, _enemy.x_pos, _enemy.y_pos);
			_enemy.x_pos -= 0.2;
			if (_enemy.x_pos < 0) {
				_enemy.x_pos = 1280;
				_enemy.y_pos = rand() % 720;
			}
			
			
			
			
		}
		
		
		//render player
		window.render(player, player.getX(), player.getY());
		//set condition position
		{if (player.y_pos < 0) player.y_pos = 0;
		if (player.y_pos > 720) player.y_pos = 720;
		if (player.x_pos < 0) player.x_pos = 0;
		if (player.x_pos > 1280) player.x_pos = 1280;

		}
		//window.render(p_bull,p_bull.x_pos ,p_bull.y_pos );
		//render bullet for player
		for (int i = 0; i < bullet_list.size(); i++) {
			bullet& bull = bullet_list[i];
			bull.x_pos = bull.x_pos + 1;
			window.render(bull, bull.x_pos, bull.y_pos);
			if (bull.x_pos > 1280) bullet_list.erase(bullet_list.begin()+i);
		}
		//DRAW LINE
		//window.drawlink(player.x_pos+24, player.y_pos+24, bull.x_pos, bull.y_pos);
		
		window.display();
		
	}

	window.cleanUp();
	SDL_Quit();

	return 0;
}
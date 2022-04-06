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

bool checkCollision(SDL_Rect a, SDL_Rect b)
{
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	//Calculate the sides of rect B
	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;

	//If any of the sides from A are outside of B
	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	//If none of the sides from A are outside B
	return true;
}

int main(int argc, char* args[])
{
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
		std::cout << "HEY.. SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;

	if (!(IMG_Init(IMG_INIT_PNG)))
		std::cout << "IMG_init has failed. Error: " << SDL_GetError() << std::endl;

	RenderWindow window("GAME v1.0", 1280 , 720 );
	
	
	//get texture
	SDL_Texture* background = window.loadTexture("D:/Asteroid UET/image/background.png");
	SDL_Texture* pilot= window.loadTexture("D:/Asteroid UET/image/player-Copy.png");
	SDL_Texture* pow = window.loadTexture("D:/Asteroid UET/image/alienBullet.png");
	SDL_Texture* p_enemy= window.loadTexture("D:/Asteroid UET/image/enemy.png");
	SDL_Texture* pow_enemy = window.loadTexture("D:/Asteroid UET/image/enemyBullet.png");
	
	
	//init object
	player player(pilot);
	enemy Enemy(p_enemy);
	bullet p_bull(pow,player.getX(),player.getY());
	bullet enemy_bull(pow_enemy);
	vector <bullet> enemy_bulls;
	vector <bullet> bullet_list;
	vector <enemy> enemy_team;

	bool gameRunning = true;
	
	//init enemy
	for (int i = 0; i < 4; i++) {
		enemy_team.push_back(Enemy);
		enemy_team[i].y_pos= rand()%720+i*145;
		if (enemy_team[i].y_pos > 720-48) enemy_team[i].y_pos *= 0.2;
		enemy_team[i].x_pos = 1280 + i * 190;
	}
	SDL_Event event;
	
	while (gameRunning)
	{
		// Get our controls and events
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				gameRunning = false;


			player.move(event, player.x_pos, player.y_pos, player.gun );
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
			
			//set mCollider
			_enemy.mCollider.x = _enemy.x_pos;
			_enemy.mCollider.y = _enemy.y_pos;
			window.render(_enemy, _enemy.x_pos, _enemy.y_pos);
			_enemy.x_pos -= 0.2; _enemy.mCollider.x = _enemy.x_pos;
			/*if (SDL_HasIntersection(&_enemy.mCollider, &player.mCollider)) {
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Info", "CUT LUON!", NULL);
				SDL_Quit();
			}*/
			if (_enemy.x_pos < 0) {
				_enemy.x_pos = 1280;
				_enemy.y_pos = rand() % 672;
				
				_enemy.mCollider.x = _enemy.x_pos;
				_enemy.mCollider.y = _enemy.y_pos;
				
				enemy_bull.x_pos = _enemy.x_pos;
				enemy_bull.y_pos = _enemy.y_pos;
				
				
				enemy_bull.mCollider.x = _enemy.x_pos;
				enemy_bull.mCollider.y = _enemy.y_pos;

				if (enemy_bulls.size() > 4) continue;
				else
				{
					enemy_bulls.push_back(enemy_bull);

				}
			}
			
				
		}
		
		for (int i = 0; i < enemy_bulls.size(); i++) {
			bullet& e_bull = enemy_bulls[i];
			e_bull.x_pos = e_bull.x_pos - 0.5;
			enemy_bull.mCollider.x = e_bull.x_pos;
			enemy_bull.mCollider.y = e_bull.y_pos;
			if (checkCollision(e_bull.mCollider, player.mCollider)) cout << "X";
			window.render(e_bull, e_bull.x_pos, e_bull.y_pos);
			
			
			// get e_bull Collider and check player vs enemy_bull
			e_bull.mCollider.x = e_bull.x_pos;
			e_bull.mCollider.y = e_bull.y_pos;
			
			/*if (SDL_HasIntersection(&e_bull.mCollider, &player.mCollider)) {
				cout << "ban da chet lan n";
			}*/


			if (e_bull.x_pos < 0) enemy_bulls.erase(enemy_bulls.begin() + i);

		}
		
		
		//render player
		window.render(player, player.getX(), player.getY());

		//set condition position
		{if (player.y_pos < 0) player.y_pos = 0;
		if (player.y_pos > 720-48) player.y_pos = 720-48;
		if (player.x_pos < 0) player.x_pos = 0;
		if (player.x_pos > 1280-46) player.x_pos = 1280-46;

		}
		//window.render(p_bull,p_bull.x_pos ,p_bull.y_pos );
		//render bullet for player
		for (int i = 0; i < bullet_list.size(); i++) {
			bullet& bull = bullet_list[i];
			bull.x_pos = bull.x_pos + 1;
			
			window.render(bull, bull.x_pos, bull.y_pos);
			
			//set mCollider bull
			bull.mCollider.x = bull.x_pos;
			bull.mCollider.y = bull.y_pos;
			cout << bull.mCollider.h;
			// 
			for (auto &_enemy : enemy_team)
			{
				if (SDL_HasIntersection(&bull.mCollider, &_enemy.mCollider)) {
					_enemy.x_pos = 1280;
					_enemy.y_pos = rand() % 672;
					cout << "thay bi ban ";
				}
			}

			if (bull.x_pos > 1280) bullet_list.erase(bullet_list.begin() + i);

		}
		//DRAW LINE
		//window.drawlink(player.x_pos+24, player.y_pos+24, bull.x_pos, bull.y_pos);
		
		window.display();
		
	}
	
	window.cleanUp();
	SDL_Quit();

	return 0;
}
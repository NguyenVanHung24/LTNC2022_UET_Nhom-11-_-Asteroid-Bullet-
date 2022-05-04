
#include <SDL_mixer.h>
#include <algorithm>
#include <iostream>
#include <ctime>
#include "image.h"
#include "player.h"
#include "entity.h"
#include "enemy.h"
#include "bullet.h"
#include "explosion.h"
#include <vector>
using namespace std;

const int EXPLOSION_FRAME = 13;

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
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) > 0)
		std::cout << "HEY.. SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;

	if (!(IMG_Init(IMG_INIT_PNG)))
		std::cout << "IMG_init has failed. Error: " << SDL_GetError() << std::endl;
	if (TTF_Init() == -1)
	{
		cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError();
		
	}
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << endl;
	}

	RenderWindow window("GAME v1.0", 1280, 720 );

	// music
	Mix_Music* gMusic = NULL;
	gMusic = Mix_LoadMUS("D:/Asteroid UET/music/Mercury.ogg");
	// sound effect
	Mix_Chunk* player_fire = NULL;
	Mix_Chunk* enemy_die = NULL;
	player_fire = Mix_LoadWAV("D:/Asteroid UET/sound/player_fire.ogg");
	enemy_die = Mix_LoadWAV("D:/Asteroid UET/sound/shotgun.ogg");
	if (gMusic == NULL)
	{
		cout << "Failed to load music\n";
	}
	
	// play music
	if (Mix_PlayingMusic() == 0)
	{
		//Play the music
		Mix_PlayMusic(gMusic, -1);
	}
	
	//get texture
	SDL_Texture* background = window.loadTexture("D:/Asteroid UET/image/aka.png");
	SDL_Texture* pilot= window.loadTexture("D:/Asteroid UET/image/player-Copy.png");
	SDL_Texture* pow = window.loadTexture("D:/Asteroid UET/image/playerBullet.png");
	SDL_Texture* p_enemy= window.loadTexture("D:/Asteroid UET/image/enemy.png");
	SDL_Texture* pow_enemy = window.loadTexture("D:/Asteroid UET/image/enemyBullet.png");
	SDL_Texture* explode = window.loadTexture("D:/Asteroid UET/image/spritesheet.png");
	SDL_Texture* backgroungimage=window.loadTexture("D:/Asteroid UET/image/menubgr1.png");
	SDL_Texture* highscore = window.loadTexture("D:/Asteroid UET/image/highscore.png");
	//init object
	player player(pilot);
	enemy Enemy(p_enemy);
	bullet p_bull(pow,player.getX(),player.getY());
	bullet enemy_bull(pow_enemy);
	vector <bullet> enemy_bulls;
	vector <bullet> bullet_list;
	vector <enemy> enemy_team;
	SDL_Rect rect[4];
	Explosion explo(explode);

	

	// load explosion
	explo.loadExplosion();
	
	//init enemy
	for (int i = 0; i < 4; i++) {
		enemy_team.push_back(Enemy);
		enemy_team[i].y_pos= rand()%720+i*145;
		if (enemy_team[i].y_pos > 720-48) enemy_team[i].y_pos *= 0.2;
		enemy_team[i].x_pos = 1280 + i * 190;
	}
	SDL_Event event;
	int score[100] = {0};
	int turn = 0;
	int start = 3;
	int point=0;
	int frame = 0;
	bool gameRunning = true;
	
	while (gameRunning)
	{
		// Get our controls and events
		SDL_PollEvent(&event);
		{
			if (event.type == SDL_QUIT)
				gameRunning = false;
		}
		window.clear();
		{if (start == 3)
		{
			window.render(backgroungimage);
			window.rendertext("START", 60, 555, 250,rect[0]);
			window.rendertext("HIGH SCORE", 60, 468, 350,rect[1]);
			window.rendertext("EXIT", 60, 578, 450,rect[2]);
			window.handleEvent(event, start, rect);
			window.display();
		}}
		if (start == 1) {
			window.clear();
			
			window.render(highscore);
			window.rendertext("Turn Back", 60, 900, 650, rect[3]);
			for (int j = 1; j <= 10; j++)
			{
				string tmp = "TOP  " + to_string(j);
				window.rendertext(tmp.c_str(), 45, 100, 150 + 40 * j);

			}
			sort(score, score+100,greater<int>());
			for (int j = 1; j <= 10; j++)
			{	
				string tmp = to_string(score[j-1]);
				window.rendertext(tmp.c_str(), 45, 720, 150 + 40 * j);

			}
			window.handleEvent(event, start, rect);
			window.display();
		}
		if (start == 2)
		{
			gameRunning = false;
			break;
		}
		if (start == 0) {
			window.render(background);

			player.move(event, player.x_pos, player.y_pos, player.gun);
			//make bullet for player
			if (player.gun == true) {
				//play fire sound effect
				Mix_PlayChannel(-1, player_fire, 0);
				p_bull.x_pos = player.x_pos + 36;
				p_bull.y_pos = player.y_pos + 18;
				bullet_list.push_back(p_bull);
				player.gun = false;
			}
		

		//render enemy team and bull
		for (int i = 0; i < 4; i++) {
			enemy& _enemy = enemy_team[i];

			//set mCollider
			_enemy.mCollider.x = _enemy.x_pos;
			_enemy.mCollider.y = _enemy.y_pos;
			window.render(_enemy, _enemy.x_pos, _enemy.y_pos);
			_enemy.x_pos -= 0.2; _enemy.mCollider.x = _enemy.x_pos;
			if (checkCollision(_enemy.mCollider, player.mCollider)) {
				while (frame < 390) {
					frame++;
					SDL_Rect* currentClip = &explo.explode[frame / 30];
					window.renderExplosion(player.x_pos - 50, player.y_pos - 75, currentClip, explode);
					SDL_RenderPresent(window.renderer);
				}
				player.x_pos = 0;
				player.y_pos = 0;
				player.mCollider.x = 0;
				player.mCollider.y = 0;
				_enemy.x_pos=1280;
				_enemy.y_pos = 620;
				cout << point<<endl;
				score[turn]=point;
				cout << turn;
				point = 0;
				turn=turn +1;
				start = 3; window.clear();
				break;
			}
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
			if (checkCollision(e_bull.mCollider, player.mCollider)) {
				while (frame < 390) {
					frame++;
					SDL_Rect* currentClip = &explo.explode[frame / 30];
					window.renderExplosion(player.x_pos - 50, player.y_pos - 75, currentClip, explode);
					SDL_RenderPresent(window.renderer);
				}
				start = 3; window.clear();
				player.mCollider.x = 0;
				player.mCollider.y = 0;
				player.x_pos = 0;
				player.y_pos = 0;
				score[turn]=point;
				turn++;
				point = 0;
				enemy_bulls.erase(enemy_bulls.begin() + i);
				break;
			}
			window.render(e_bull, e_bull.x_pos, e_bull.y_pos);


			// get e_bull Collider and check player vs enemy_bull
			e_bull.mCollider.x = e_bull.x_pos;
			e_bull.mCollider.y = e_bull.y_pos;


			if (e_bull.x_pos < 0) enemy_bulls.erase(enemy_bulls.begin() + i);

		}


		//render player
		window.render(player, player.x_pos, player.y_pos);



		//set condition position
		{if (player.y_pos < 0) player.y_pos = 0;
		if (player.y_pos > 720 - 48) player.y_pos = 720 - 48;
		if (player.x_pos < 0) player.x_pos = 0;
		if (player.x_pos > 1280 - 46) player.x_pos = 1280 - 46;

		}
		
		//render bullet for player
		for (int i = 0; i < bullet_list.size(); i++) {
			bullet& bull = bullet_list[i];
			bull.x_pos = bull.x_pos + 1;
			if (start == 3) bullet_list.clear();
			window.render(bull, bull.x_pos, bull.y_pos);

			//set mCollider bull
			bull.mCollider.x = bull.x_pos;
			bull.mCollider.y = bull.y_pos;
			// 
			for (auto& _enemy : enemy_team)
			{
				if (checkCollision(bull.mCollider, _enemy.mCollider)) {
					int framex = 0;
					while (framex < 390) {
						framex++;
						SDL_Rect* currentClip = &explo.explode[framex / 30];
						window.renderExplosion(bull.x_pos - 50, bull.y_pos - 75, currentClip, explode);
						Mix_PlayChannel(-1, enemy_die, 0);
						SDL_RenderPresent(window.renderer);
					}
					_enemy.x_pos = 1280;
					_enemy.y_pos = rand() % 672;
					point++;
				}
			}
			
			if (bull.x_pos > 1280) bullet_list.erase(bullet_list.begin() + i);

		}
		string s = to_string(point);
		window.loadTextureFromText("SCORE", 900, 0);
		window.loadTextureFromText(s, 1150, 0);
		window.display();
		}
	}
	
	

	
	window.cleanUp();
	SDL_Quit();

	return 0;
}
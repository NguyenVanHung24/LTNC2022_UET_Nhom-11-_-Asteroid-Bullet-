
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
#include "time.h"
#include <vector>
#include <fstream>
using namespace std;

const int EXPLOSION_FRAME = 6;


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

	RenderWindow window("GAME v1.0", 1280, 720);

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

	//sound
	int sound = 1;

	//pause
	int pause = 0;

	//timer
	Timer timer;
	timer.start();
	const int FPS=60;
	const int frameDelay = 1000 / FPS;
	int frametime;
	Uint32  lasttime = 0, currentTime;
	//get texture
	SDL_Texture* background = window.loadTexture("D:/Asteroid UET/image/aka.png");
	SDL_Texture* pilot = window.loadTexture("D:/Asteroid UET/image/player-Copy.png");
	SDL_Texture* pow = window.loadTexture("D:/Asteroid UET/image/playerBullet.png");
	SDL_Texture* p_enemy = window.loadTexture("D:/Asteroid UET/image/enemy.png");
	SDL_Texture* pow_enemy = window.loadTexture("D:/Asteroid UET/image/enemyBullet.png");
	SDL_Texture* explode = window.loadTexture("D:/Asteroid UET/image/spritesheet.png");
	SDL_Texture* backgroungimage = window.loadTexture("D:/Asteroid UET/image/menubgr1.png");
	SDL_Texture* highscore = window.loadTexture("D:/Asteroid UET/image/highscore.png");
	SDL_Texture* square = window.loadTexture("D:/Asteroid UET/image/square.png");
	SDL_Texture* button = window.loadTexture("D:/Asteroid UET/image/button.png");
	SDL_Texture* bar = window.loadTexture("D:/Asteroid UET/image/scorebar.png");
	SDL_Texture* menubgr = window.loadTexture("D:/Asteroid UET/image/akabgr.png");
	SDL_Texture* aboutscreen = window.loadTexture("D:/Asteroid UET/image/aboutscreen.png");
	SDL_Texture* gameover = window.loadTexture("D:/Asteroid UET/image/gameover.png");
	
	//init object
	player player(pilot);
	enemy Enemy(p_enemy);
	
	bullet p_bull(pow, player.getX(), player.getY());
	bullet enemy_bull(pow_enemy);
	vector <bullet> enemy_bulls;
	vector <bullet> bullet_list;
	vector <enemy> enemy_team;
	SDL_Rect rect[7]; // buttons in the game
	SDL_Rect buttonrect[5];
	Explosion explo(explode);
	bool reset = false;

	//init boss
	SDL_Texture* boss = window.loadTexture("D:/Asteroid UET/image/boss.png");
	enemy Boss(boss);
	Boss.mCollider.x = -1000;
	Boss.mCollider.y = -1000;
	

	SDL_Texture* boss_bull = window.loadTexture("D:/Asteroid UET/image/biglaser.png");
	bullet boss_aks(boss_bull,1100,300);
	vector<bullet> boss_bulls;
	int healthpoint = 20;
	bool live = false;
	
	//file
	fstream f;

	SDL_Texture* startmenu = window.loadTextureFromText("START", 585, 200, 60);
	SDL_Texture* highscoremenu=window.loadTextureFromText("HIGH SCORE", 515, 320, 60);
	SDL_Texture* about=window.loadTextureFromText("ABOUT", 575, 440, 60);
	SDL_Texture* exit=window.loadTextureFromText("EXIT", 598, 560, 60);
	SDL_Texture* quit = window.loadTextureFromText("QUIT", 598, 560, 60);
	SDL_Texture* continuegame = window.loadTextureFromText("CONTINUE", 598, 560, 60);

	// load explosion
	explo.loadExplosion();

	//init text
	SDL_Texture* P = window.loadTextureFromText("SCORE", 800, 0, 60);
	SDL_Texture* Point[500] = {NULL};
	for (int i = 0; i < 500; i++) {
		string temp = to_string(i);
		Point[i] = window.loadTextureFromText(temp, 1150, 0, 60);
	}

	//init ui button
	buttonrect[0].x = 32;
	buttonrect[0].y = 32;
	buttonrect[0].w = 16;
	buttonrect[0].h = 16;

	buttonrect[1].x = 16;
	buttonrect[1].y = 32;
	buttonrect[1].w = 16;
	buttonrect[1].h = 16;

	buttonrect[2].x = 16;
	buttonrect[2].y = 16;
	buttonrect[2].w = 16;
	buttonrect[2].h = 16;

	buttonrect[3].x = 32;
	buttonrect[3].y = 0;
	buttonrect[3].w = 16;
	buttonrect[3].h = 16;

	buttonrect[4].x = 0;
	buttonrect[4].y = 0;
	buttonrect[4].w = 345;
	buttonrect[4].h = 76;
	
	//init enemy
	for (int i = 0; i < 4; i++) {
		enemy_team.push_back(Enemy);
		enemy_team[i].y_pos= rand()%720 + i*145;
		if (enemy_team[i].y_pos > 720-48) enemy_team[i].y_pos *=8;
		if (enemy_team[i].y_pos < 100) enemy_team[i].y_pos = 100;
		enemy_team[i].x_pos = 1280 + i * 190;
	}
	SDL_Event event;
	vector <int> score;
	int turn = 0;
	int start = 3;
	int point=0;
	int tmp = 0;
	int frameend = 0;
	bool dead = false;
	int deadtime = 0;
	vector<int> frame;
	vector<int> x_explosion;
	vector<int> y_explosion;
	bool gameRunning = true;
	f.open("D:/Asteroid UET/Asteroid UET/highscore.txt", ios::in);
	while (!f.eof())
	{
		int tmpscore;
		f >> tmpscore;
		score.push_back(tmpscore);
	}
	f.close();
	//timer.start();
	while (gameRunning)
	{
		
		//pGet our controls and events
		SDL_PollEvent(&event);
		{
			if (event.type == SDL_QUIT)
				gameRunning = false;
		}
		window.clear();
		if ((timer.getTicks() > deadtime) && (dead == true)) {
			
			for (int i = 5; i >= 0; i--) {
				window.render(gameover);
				window.rendertext("YOUR SCORE:", 60, 470, 260);
				window.rendertext("BACK TO MAIN SCREEN IN", 60, 370, 350);
				string secondsleft = to_string(i);
				SDL_Texture* secs = window.loadTextureFromText(secondsleft, 1150, 0, 60);
				window.render(920, 350, secs);
				window.render(820, 260, Point[point]);
				SDL_RenderPresent(window.renderer);
				SDL_Delay(1000);
			}
			point = 0;
			turn = turn + 1;
			reset = true;
			deadtime = 0;
			dead = false;
			start = 3; window.clear();
		}
		else {
			if (start == 3)
			{//menu
				//reset game 
				if (reset == true) {

					player.mCollider.x = 0;
					player.mCollider.y = 0;
					player.x_pos = 0;
					player.y_pos = 0;

					boss_bulls.clear();
					enemy_bulls.clear();
					bullet_list.clear();
					for (auto& _enemy : enemy_team) {
						_enemy.x_pos += 1280;
						_enemy.mCollider.x = _enemy.x_pos;
					}
					healthpoint = 20;
					score.push_back(point);
					f.open("D:/Asteroid UET/Asteroid UET/highscore.txt", ios::app);
					f << point << " ";
					point = 0;
					reset = false;
				}

				//timer.pause();
				window.render(backgroungimage);
				window.renderPortion(470, 215, 345, 76, &buttonrect[4], square, rect[0]);
				window.renderPortion(470, 335, 345, 76, &buttonrect[4], square, rect[1]);
				window.renderPortion(470, 455, 345, 76, &buttonrect[4], square, rect[4]);
				window.renderPortion(470, 575, 345, 76, &buttonrect[4], square, rect[2]);
				window.render(585, 200, startmenu);
				window.render(515, 320, highscoremenu);
				window.render(575, 440, about);
				window.render(598, 560, exit);
				window.handleEvent(event, start, rect, pause);

				// sound handle
				if (sound == 1) window.renderPortion(30, 620, 75, 75, &buttonrect[0], button, rect[5]);
				else window.renderPortion(30, 620, 75, 75, &buttonrect[1], button, rect[5]);
				window.handleState(event, sound, rect[5], window.window);
				if (sound == 0) Mix_PauseMusic();
				else Mix_ResumeMusic();


				window.display();

			}
			if (start == 1) {
				//highscore
				//timer.pause();
				window.clear();
				window.render(highscore);
				window.render(825, 605, square);
				window.rendertext("Turn Back", 50, 900, 600, rect[3]);
				for (int j = 1; j <= 10; j++)
				{
					string tmp = "TOP  " + to_string(j);
					window.rendertext(tmp.c_str(), 45, 500, 100 + 40 * j);

				}
				sort(score.begin(), score.end(), greater<int>());
				if (score.size() >= 10)
					for (int j = 1; j <= 10; j++)
					{
						string tmp = to_string(score[j - 1]);
						window.rendertext(tmp.c_str(), 45, 720, 100 + 40 * j);

					}
				else {
					for (int j = 1; j <= score.size(); j++)
					{
						string tmp = to_string(score[j - 1]);
						window.rendertext(tmp.c_str(), 45, 720, 100 + 40 * j);

					}
					for (int j = score.size() + 1; j <= 10; j++) {
						string tmp = to_string(0);
						window.rendertext(tmp.c_str(), 45, 720, 100 + 40 * j);
					}
				}
				window.handleEvent(event, start, rect, pause);
				window.display();
			}
			if (start == 2)
			{
				//timer.pause();
				gameRunning = false;
				break;
			}
			if (start == 0) {
				if (pause == 0) {
					window.render(background);
					currentTime = timer.getTicks();
					window.render(0, 0, bar);

					// sound handle
					if (sound == 1) window.renderPortion(1080, 10, 75, 75, &buttonrect[0], button, rect[5]);
					else window.renderPortion(1080, 10, 75, 75, &buttonrect[1], button, rect[5]);
					window.handleState(event, sound, rect[5], window.window);

					if (sound == 0) Mix_PauseMusic();
					else Mix_ResumeMusic();

					//pause button
					window.renderPortion(1180, 10, 75, 75, &buttonrect[2], button, rect[6]);
					window.handleState(event, pause, rect[6], window.window);

					player.move(event, player.x_pos, player.y_pos, player.gun);
					//make bullet for player
					if (player.gun == true) {
						//play fire sound effect
						if (sound == 1)Mix_PlayChannel(-1, player_fire, 0);
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
						_enemy.x_pos -= 5; _enemy.mCollider.x = _enemy.x_pos;
						if (checkCollision(_enemy.mCollider, player.mCollider)) {
							frame.push_back(0);
							x_explosion.push_back(_enemy.mCollider.x - 50);
							y_explosion.push_back(_enemy.mCollider.y - 75);
							dead = true;
							_enemy.x_pos = 1280;
							_enemy.y_pos = rand() % 672;
							deadtime = currentTime + 500;
						}
						if (_enemy.x_pos < 0) {
							_enemy.x_pos = 1280;
							_enemy.y_pos = rand() % 672;
							if (_enemy.y_pos < 100) _enemy.y_pos += 100;

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
					//enemy_bulls
					for (int i = 0; i < enemy_bulls.size(); i++) {
						bullet& e_bull = enemy_bulls[i];
						e_bull.x_pos = e_bull.x_pos - 8;
						enemy_bull.mCollider.x = e_bull.x_pos;
						enemy_bull.mCollider.y = e_bull.y_pos;
						if (checkCollision(e_bull.mCollider, player.mCollider)) {
							frame.push_back(0);
							x_explosion.push_back(e_bull.mCollider.x - 50);
							y_explosion.push_back(e_bull.mCollider.y - 75);
							dead = true;
							enemy_bulls.erase(enemy_bulls.begin() + i);
							deadtime = currentTime + 500;
						}
						window.render(e_bull, e_bull.x_pos, e_bull.y_pos);


						// get e_bull Collider and check player vs enemy_bull
						e_bull.mCollider.x = e_bull.x_pos;
						e_bull.mCollider.y = e_bull.y_pos;


						if (e_bull.x_pos < 0) enemy_bulls.erase(enemy_bulls.begin() + i);

					}


					//render player
					if (!dead) window.render(player, player.x_pos, player.y_pos);



					//set condition position
					{if (player.y_pos < 100) player.y_pos = 100;
					if (player.y_pos > 720 - 48) player.y_pos = 720 - 48;
					if (player.x_pos < 0) player.x_pos = 0;
					if (player.x_pos > 1280 - 46) player.x_pos = 1280 - 46;

					}

					//render bullet for player
					for (int i = 0; i < bullet_list.size(); i++) {
						bullet& bull = bullet_list[i];
						bull.x_pos = bull.x_pos + 8;

						window.render(bull, bull.x_pos, bull.y_pos);
						//set mCollider bull
						bull.mCollider.x = bull.x_pos;
						bull.mCollider.y = bull.y_pos;
						// 
						bool bullet_erased = false;
						for (auto& _enemy : enemy_team)
						{
							if (checkCollision(bull.mCollider, _enemy.mCollider)) {
								frame.push_back(0);
								x_explosion.push_back(_enemy.mCollider.x - 50);
								y_explosion.push_back(_enemy.mCollider.y - 75);
								bullet_erased = true;
								_enemy.x_pos = 1280;
								_enemy.y_pos = rand() % 672 + 100;
								point++;
							}


						}
						if (checkCollision(bull.mCollider, Boss.mCollider)) {
							//frame.push_back(0);

							bullet_erased = true;
							healthpoint = healthpoint - 1;
							cout << "SOS1";
							//if(healthpoint ==0) in vụ nổ phát ::)

						}
						if ((bull.x_pos > 1280) || (bullet_erased == true)) bullet_list.erase(bullet_list.begin() + i);

					}

					timer.unpause();

					//if (currentTime % 1000 == 0) cout << currentTime;
					if (point > 15 && healthpoint > 0) live = true;
					else live = false;
					if (live == true) {
						{ window.render(1100, 300, boss);
						Boss.mCollider.x = 1100;
						Boss.mCollider.y = 300;
						if (currentTime > lasttime + 3000) {
							boss_aks.caculate(player.x_pos, player.y_pos, boss_aks.x_pos, boss_aks.y_pos);
							boss_aks.dicrect_x = boss_aks.v1;
							boss_aks.dicrect_y = boss_aks.v2;
							boss_bulls.push_back(boss_aks);

							lasttime = currentTime;

						}

						}
						//boss bullet
						for (int index = 0; index < boss_bulls.size(); index++) {
							auto& boss_dan = boss_bulls[index];
							window.render(boss_dan, boss_dan.x_pos, boss_dan.y_pos);



							boss_dan.x_pos += boss_dan.dicrect_x * 5;
							boss_dan.y_pos += boss_dan.dicrect_y * 5;
							if (boss_dan.x_pos < 0)
							{
								boss_bulls.erase(boss_bulls.begin() + index);

							}
							boss_dan.mCollider.x = boss_dan.x_pos;
							boss_dan.mCollider.y = boss_dan.y_pos;
							if (checkCollision(boss_dan.mCollider, player.mCollider)) {
								frame.push_back(0);
								x_explosion.push_back(boss_dan.mCollider.x - 50);
								y_explosion.push_back(boss_dan.mCollider.y - 75);
								dead = true;
								boss_bulls.erase(boss_bulls.begin() + index);
								deadtime = currentTime + 500;
							}

						}
					}

					window.render(50, 0, P);
					window.render(250, 0, Point[point]);
					if (frame.size() >= 1) {
						if (frame[frame.size() - 1] < 30) {
							frame[frame.size() - 1]++;
							SDL_Rect* currentClip = &explo.explode[frame[frame.size() - 1] / 5];
							window.renderExplosion(x_explosion[frame.size() - 1], y_explosion[frame.size() - 1], currentClip, explode);
							if (sound == 1)Mix_PlayChannel(-1, enemy_die, 0);
							SDL_RenderPresent(window.renderer);
						}
					}
					frametime = timer.getTicks() - currentTime;
					if (frameDelay > frametime) {
						SDL_Delay(frameDelay - frametime);
					}
					window.display();
				}
				else if (pause == 1) {
					//pause button
					//pause button
					window.render(menubgr);
					window.renderPortion(470, 250, 345, 76, &buttonrect[5], square, rect[6]);
					window.renderPortion(470, 400, 345, 76, &buttonrect[5], button, rect[3]);
					window.render(470, 250, square);
					window.render(470, 400, square);
					window.render(540, 235, continuegame);
					window.render(600, 385, quit);
					window.handleState(event, pause, rect[6], window.window);
					window.handleQuit(event, start, rect[3], window.window);
					if (start == 3) reset = true;
					SDL_Delay(100);
					window.display();
				}
			}
			if (start == 4) {
				//background
				window.render(backgroungimage);
				//timer.pause();
				//text
				window.render(335, 180, aboutscreen);
				window.render(825, 605, square);
				window.rendertext("Turn Back", 50, 900, 600, rect[3]);

				window.handleEvent(event, start, rect, pause);
				window.display();
			}
		}
	}
	
	

	f.close();
	window.cleanUp();
	SDL_Quit();

	return 0;
}
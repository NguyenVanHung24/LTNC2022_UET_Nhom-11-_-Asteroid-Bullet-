#include "enemy.h"
#include "stdlib.h"
#include <ctime>
int GetRandom(int min, int max) {
	return min + (int)(rand() * (max - min + 1.0) / (1.0 + RAND_MAX));
}

enemy::enemy(SDL_Texture* p_tex) {
	tex = p_tex;
	srand(time(0));
	
	y_pos = GetRandom(0, 720);
	x_pos = 1280-40;
	
}
//void enemy::auto(std::vector<bullet> bullet) {
//}
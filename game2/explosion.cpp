
#include <SDL.h>
#include <iostream>
#include <string>
#include "explosion.h"

Explosion::Explosion(SDL_Texture* p_tex) {

	tex = p_tex;
	x_pos = 0;
	y_pos = 0;
	SDL_QueryTexture(p_tex, NULL, NULL, &width, &height);

}

bool Explosion::loadExplosion() {
	bool success = true;

	explode[0].x = 0;
	explode[0].y = 0;
	explode[0].w = 100;
	explode[0].h = 100;

	explode[1].x = 600;
	explode[1].y = 0;
	explode[1].w = 100;
	explode[1].h = 100;

	explode[2].x = 900;
	explode[2].y = 0;
	explode[2].w = 100;
	explode[2].h = 100;

	explode[3].x = 200;
	explode[3].y = 100;
	explode[3].w = 100;
	explode[3].h = 100;

	explode[4].x = 800;
	explode[4].y = 100;
	explode[4].w = 100;
	explode[4].h = 100;

	explode[5].x = 700;
	explode[5].y = 200;
	explode[5].w = 100;
	explode[5].h = 100;

	

	return success;
}

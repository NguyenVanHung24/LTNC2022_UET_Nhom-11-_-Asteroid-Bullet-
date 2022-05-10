#ifndef EXPLOSION_H
#define EXPLOSION_H
#include <SDL.h>
#include<SDL_image.h>
#include <string>
#include <iostream>
#include "entity.h"

class Explosion : public Entity {
public:
	Explosion(SDL_Texture* p_tex);

	float x_pos, y_pos;

	bool loadExplosion();
	SDL_Rect explode[6];
};



#endif
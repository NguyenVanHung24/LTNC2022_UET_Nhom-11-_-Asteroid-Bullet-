#ifndef EXPLOSION_H_
#define EXPLOSION_H_
#include "MainLib.h"
#include "entity.h"

class Explosion : public Entity {
public:
	Explosion(SDL_Texture* p_tex);

	float x_pos, y_pos;

	bool loadExplosion();
	SDL_Rect explode[6];
};



#endif
#ifndef ENEMY_H
#define ENEMY_H

#include "MainLib.h"
#include "entity.h"

class enemy : public Entity {
public:
	enemy(SDL_Texture* p_tex);
	//void auto(std::vector<bullet> bullet);
	float x_pos;
	float y_pos;
	

	// enemy's collision box
	SDL_Rect mCollider;
};
#endif
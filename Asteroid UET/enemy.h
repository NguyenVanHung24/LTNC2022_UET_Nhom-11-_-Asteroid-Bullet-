#ifndef ENEMY_H
#define ENEMY_H
#include "entity.h"
#include "bullet.h"
#include <vector>
class enemy : public Entity {
public:
	enemy(SDL_Texture* p_tex);
	//void auto(std::vector<bullet> bullet);
	float x_pos;
	float y_pos;
	float height;
	float width;

	// enemy's collision box
	SDL_Rect mCollider;
};
#endif
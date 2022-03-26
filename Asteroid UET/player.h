#pragma once

#include "entity.h"
#include <vector>
#include "image.h"
#include <iostream>
#include "bullet.h"
class player : public Entity {
public:
	player(SDL_Texture* p_tex);
	
	float getX();
	float getY();
	void set_bullet(std::vector < bullet > p_bullet) {
		bullet_list = p_bullet;
	}
	std::vector < bullet> get_bullet() {
		return bullet_list;
	}
	void move(SDL_Event events, float& x, float& y);
	float x_pos;
	float y_pos;
	int count;
	std::vector<bullet> bullet_list;
}
;
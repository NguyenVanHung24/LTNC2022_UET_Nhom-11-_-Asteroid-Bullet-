#ifndef BULLET_H
#define BULLET_H
#include <math.h>
#include "entity.h"

class bullet : public Entity
{
public:
	bullet();
	bullet(SDL_Texture* p_tex);
	bullet(SDL_Texture* p_tex, float x, float y);
	
	void move(float& x_pos);
	void caculate(float x_player, float y_player, float x, float y);
	// bullet's position
	float x_pos;
	float y_pos;
	
	float v1;
	float v2;
	float dicrect_x;
	float dicrect_y;
	// bullet's collision box
	SDL_Rect mCollider;
protected:

};
#endif

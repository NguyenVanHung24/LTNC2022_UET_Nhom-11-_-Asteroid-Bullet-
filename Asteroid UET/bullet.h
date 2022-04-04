#ifndef BULLET_H
#define BULLET_H

#include "entity.h"

class bullet : public Entity
{
public:
	bullet();
	bullet(SDL_Texture* p_tex);
	bullet(SDL_Texture * p_tex ,float x,float y);
	
	void move(float& x_pos);

	// bullet's position
	float x_pos;
	float y_pos;

	// bullet's collision box
	SDL_Rect mCollider;
protected:

};
#endif

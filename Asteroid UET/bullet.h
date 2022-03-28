#pragma once

#include "entity.h"

class bullet : public Entity
{
public:
	bullet();
	bullet(SDL_Texture * p_tex ,float x,float y);
	
	void move(float& x_pos);
	float x_pos;
	float y_pos;
protected:

};


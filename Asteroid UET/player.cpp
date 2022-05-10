#pragma once

#include "player.h"

player::player(SDL_Texture* p_tex){
	tex = p_tex;
	x_pos = 200;
	y_pos = 300;
	gun = false;
	SDL_QueryTexture(p_tex, NULL, NULL, &width, &height);
	mCollider.w = width;
	mCollider.h = height;
	
	mCollider.x = x_pos;
	mCollider.y = y_pos;
	
}
void player::move(SDL_Event events, float& x, float& y,bool& gun) {
	switch (events.key.keysym.sym)
	{
	case SDLK_UP:
		y = y - 15;
		mCollider.y = y;
		break;
	case SDLK_DOWN:
		y = y + 15;
		mCollider.y = y;
		break;
	case SDLK_LEFT:
		x = x - 15;
		mCollider.x = x;
		break;
	case SDLK_RIGHT:
		x = x + 15;
		mCollider.x = x;
		break;

	//Catch mouse button
	case SDLK_KP_SPACE:
		gun = true;
		break;
	}
	
}
float player::getX() {
	return x_pos;
}
float player::getY() {
	return y_pos;
}
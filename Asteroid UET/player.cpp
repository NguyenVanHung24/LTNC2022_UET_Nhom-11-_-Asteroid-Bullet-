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
	std::cout << mCollider.w << " " << mCollider.h << std::endl;
	mCollider.x = x_pos;
	mCollider.y = y_pos;
}
void player::move(SDL_Event events, float& x, float& y,bool& gun, SDL_Rect mCollider) {
	switch (events.key.keysym.sym)
	{
	case SDLK_UP:
		y = y - 10;
		mCollider.y = y;
		break;
	case SDLK_DOWN:
		y = y + 10;
		mCollider.y = y;
		break;
	case SDLK_LEFT:
		x = x - 10;
		mCollider.x = x;
		break;
	case SDLK_RIGHT:
		x = x + 10;
		mCollider.x = x;
		break;

	}//Catch mouse button
	if (events.type == SDL_MOUSEBUTTONDOWN) {
		gun = true;
	}
}
float player::getX() {
	return x_pos;
}
float player::getY() {
	return y_pos;
}
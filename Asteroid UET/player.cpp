#pragma once

#include "player.h"

player::player(SDL_Texture* p_tex){
	tex = p_tex;
	x_pos = 200;
	y_pos = 300;
	gun = false;
}
void player::move(SDL_Event events, float& x, float& y,bool& gun) {
	switch (events.key.keysym.sym)
	{
	case SDLK_UP:
		y = y - 10;
		std::cout << "con chim non";
		break;
	case SDLK_DOWN:
		y = y + 10;
		break;
	case SDLK_LEFT:
		x = x - 10;
		break;
	case SDLK_RIGHT:
		x = x + 10;
		break;

	}//Catch mouse button
	if (events.type == SDL_MOUSEBUTTONDOWN) {
		
		std::cout << "con chim non 3";
		gun = true;
	}
}
float player::getX() {
	return x_pos;
}
float player::getY() {
	return y_pos;
}
#include "bullet.h"
bullet::bullet() {
}
bullet::bullet(SDL_Texture* p_tex) {
	tex = p_tex;
	
}
bullet::bullet(SDL_Texture* p_tex, float x, float y ) {
	tex = p_tex;
	x_pos = x;
	y_pos = y;
	
}


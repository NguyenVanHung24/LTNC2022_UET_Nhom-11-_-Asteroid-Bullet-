#include "bullet.h"
bullet::bullet() {
}
bullet::bullet(SDL_Texture* p_tex) {
	tex = p_tex;
	SDL_QueryTexture(p_tex, NULL, NULL, &width, &height);
	mCollider.w = width;
	mCollider.h = height;
}
bullet::bullet(SDL_Texture* p_tex, float x, float y ) {
	tex = p_tex;
	x_pos = x;
	y_pos = y;
	mCollider.x = x;
	mCollider.y = y;
}


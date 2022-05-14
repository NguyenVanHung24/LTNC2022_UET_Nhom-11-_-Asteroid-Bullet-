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
	SDL_QueryTexture(p_tex, NULL, NULL, &width, &height);
	mCollider.w = width;
	mCollider.h = height;



}
void bullet::caculate(float x_player, float y_player, float x, float y) {
	v1 = x_player - x;
	v2 = y_player - y;
	float square = sqrt(v1 * v1 + v2 * v2);
	v1 = v1 / square;
	v2 = v2 / square;
}

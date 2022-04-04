
#include "entity.h"

Entity::Entity() {}
Entity::Entity(SDL_Texture* p_tex)

{
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = 64;
	currentFrame.h = 64;
	tex = p_tex;
	//get currenrframe equal source image
	SDL_QueryTexture(p_tex, NULL, NULL, &currentFrame.w, &currentFrame.h);
}
SDL_Rect Entity::getCurrentFrame()
{
	return currentFrame;
}
//void Entity::setRect(SDL_Rect& cn) {
	//currentFrame = cn;
//}

void Entity::getSize(SDL_Texture* t) {
	SDL_QueryTexture(t, NULL, NULL, &width, &height);
}


SDL_Texture* Entity::getTex()
{
	return tex;
}







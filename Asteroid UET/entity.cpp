
#include "entity.h"

Entity::Entity() {}
Entity::Entity(SDL_Texture* p_tex)

{
	
	tex = p_tex;
	//get currenrframe equal source image
	SDL_QueryTexture(p_tex, NULL, NULL, &width, &height);
}
SDL_Rect Entity::getCurrentFrame()
{
	return currentFrame;
}
//void Entity::setRect(SDL_Rect& cn) {
	//currentFrame = cn;
//}




SDL_Texture* Entity::getTex()
{
	return tex;
}







#include"EndFlag.h"
EndFlag::EndFlag(Resources::TEXTURE texture, std::shared_ptr<b2World> world, sf::Vector2f pos,Resources::SOUNDS sound)
	: StaticObject(texture, world, pos,sound)
{}

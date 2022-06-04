#pragma once
#include"StaticObject.h"
class EndFlag :public StaticObject
{
public:
	using StaticObject::StaticObject;
	EndFlag(Resources::TEXTURE, std::shared_ptr<b2World> world, sf::Vector2f pos, Resources::SOUNDS sound);

protected:

private:

};
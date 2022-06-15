#pragma once

#include"StaticObject.h"

class Coin :public StaticObject
{
public:
	using StaticObject::StaticObject;
	Coin(Resources::TEXTURE, std::shared_ptr<b2World> world, sf::Vector2f pos, Resources::SOUNDS sound);
	~Coin() = default;
	void update(sf::Time);

private:
	Animation m_animation;
};
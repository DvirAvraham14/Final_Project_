#pragma once
#include "MovingObject.h"
class Enemy : public MovingObject
{
public:
	using::MovingObject::MovingObject;
	Enemy(Resources::TEXTURE, std::shared_ptr<b2World>, sf::Vector2f, Resources::Players aniData, Resources::SOUNDS sound);
	virtual void drive(Resources::Players player = Resources::Players::P_Truck)					= 0;
	//virtual void update(sf::Time)																;
	virtual void jump(float = 0,Resources::Players = Resources::Players::MaxPlayer) {}
	virtual void CreateBody(sf::Vector2f pos);

protected:
};
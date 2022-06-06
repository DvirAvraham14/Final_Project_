#pragma once
#include "MovingObject.h"
class Enemy : public MovingObject
{
public:
	using::MovingObject::MovingObject;
	Enemy(Resources::TEXTURE, std::shared_ptr<b2World>, sf::Vector2f, Resources::Players aniData, Resources::SOUNDS sound);
	virtual void drive(int)       =0;
	virtual void update(sf::Time) = 0;
	virtual void jump(int ) {}
	virtual void CreateBody(sf::Vector2f pos);

protected:
};
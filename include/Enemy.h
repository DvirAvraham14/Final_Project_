#pragma once
#include "MovingObject.h"
class Enemy : public MovingObject
{
public:
	using::MovingObject::MovingObject;
	Enemy(Resources::TEXTURE, std::shared_ptr<b2World>, sf::Vector2f, Resources::Players aniData);
	virtual void drive(int speed = 20) = 0;
	void jump(int jump = 50) {}
	void checkAndGo(sf::Time time);
	virtual void CreateBody(sf::Vector2f pos);

protected:
};
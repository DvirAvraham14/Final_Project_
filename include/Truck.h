#pragma once
#include "Enemy.h"
class Truck : public Enemy
{

public:
	using Enemy::Enemy;
	Truck(Resources::TEXTURE, std::shared_ptr<b2World>, sf::Vector2f , Resources::Players , Resources::SOUNDS);
	virtual void drive(int);
	virtual void update(sf::Time);
private:
	bool m_goRight =true;
};
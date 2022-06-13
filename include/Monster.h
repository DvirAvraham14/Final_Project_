#pragma once
#include "Enemy.h"
class Monster : public Enemy
{

public:
	using Enemy::Enemy;
	Monster(Resources::TEXTURE, std::shared_ptr<b2World>, sf::Vector2f, Resources::Players, Resources::SOUNDS);
	virtual void drive(Resources::Players = Resources::Players::P_Monster);
	virtual void update(sf::Time);
private:
	sf::Vector2f m_posA;
	sf::Vector2f m_posB;
	bool m_goRight = true;
};
#pragma once
#include "Enemy.h"
class Monster : public Enemy
{

public:
	using Enemy::Enemy;
	Monster(Resources::TEXTURE, std::shared_ptr<b2World>, sf::Vector2f , Resources::Players );
	virtual void drive(int speed = 20);
private:
	sf::Vector2f m_posA;
	sf::Vector2f m_posB;
	bool m_move=true;
	bool m_goRight =true;
};
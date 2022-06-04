#include"Monster.h"
Monster::Monster(Resources::TEXTURE texture, std::shared_ptr<b2World> world, sf::Vector2f pos, Resources::Players aniData, Resources::SOUNDS sound)
	:Enemy(texture, world, pos, aniData,sound),
	m_posA(pos),
	m_posB(pos + sf::Vector2f(200,0))
{
	auto size = m_sprite.getGlobalBounds();
	m_sprite.setOrigin(size.width/2, size.height/2);
}

void Monster::update(sf::Time) {
	drive(7);
	b2Vec2  position = m_body->GetPosition();
	float	angle = 180 / b2_pi * m_body->GetAngle();
	m_sprite.setPosition(position.x, position.y);
	m_sprite.setRotation(angle);
}

void Monster::drive(int speed) {
	if (m_body->GetPosition().x >= m_posB.x)
	m_goRight = false;
	else if (m_body->GetPosition().x <= m_posA.x)
	m_goRight = true;
	
	if (!m_goRight) 
		speed *= -1;
	
		m_body->SetLinearVelocity(b2Vec2(speed, 0));
}

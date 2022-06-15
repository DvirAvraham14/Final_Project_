#include"Monster.h"

//___________________________________________________

Monster::Monster(Resources::TEXTURE texture, std::shared_ptr<b2World> world, sf::Vector2f pos, Resources::Players aniData, Resources::SOUNDS sound)
	:Enemy(texture, world, pos, aniData, sound),
	m_posA(pos),
	m_posB(pos + MONSTER_POS)

{
	auto size = m_sprite.getGlobalBounds();
	m_sprite.setOrigin(size.width / HALF, size.height / HALF);

}

//___________________________________________________

void Monster::update(sf::Time delta) {
	drive();
	b2Vec2  position = m_body->GetPosition();
	float	angle = ANGLE / b2_pi * m_body->GetAngle();
	m_sprite.setPosition(position.x, position.y);
	m_sprite.setRotation(angle);
	m_animation.update(delta);
}

//___________________________________________________

void Monster::drive(Resources::Players player) {
	m_speed = MAX_SPEED[Resources::Players::P_Monster];
	if (m_body->GetPosition().x >= m_posB.x)
		m_goRight = false;

	else if (m_body->GetPosition().x <= m_posA.x)
		m_goRight = true;

	if (!m_goRight) {
		m_sprite.setScale(MOVE_LEFT);
		m_speed *= REVERS;
	}
	else
		m_sprite.setScale(MOVE_RIGHT);

	m_body->SetLinearVelocity(b2Vec2(m_speed, RESET));
}


#include"Scate.h"

void Scate::draw(sf::RenderWindow& target) {
	b2Vec2 position = m_body->GetPosition();
	position *= SCALAR;
	float angle = 180 / b2_pi * m_body->GetAngle();
	m_sprite.setPosition(position.x, position.y);
	m_sprite.setRotation(angle);
	target.draw(m_sprite);
}
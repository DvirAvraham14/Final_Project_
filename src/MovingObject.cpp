#include"MovingObject.h"

void MovingObject::update() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		jump();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		drive();
	b2Vec2  position = m_body->GetPosition();
	float	angle = 180 / b2_pi * m_body->GetAngle();
	m_sprite.setPosition(position.x, position.y);
	m_sprite.setRotation(angle);
}
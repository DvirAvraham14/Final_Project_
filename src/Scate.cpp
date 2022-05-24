#include"Scate.h"

void Scate::draw(sf::RenderWindow& target) {
	b2Vec2 position = m_body->GetPosition();
	position *= SCALAR;
	float angle = 180 / b2_pi * m_body->GetAngle();
	m_sprite.setPosition(position.x, position.y);
	m_sprite.setRotation(angle);
	target.draw(m_sprite);
}
void Scate::drive() {
	m_body->ApplyLinearImpulse(b2Vec2(0.83,0),m_body->GetWorldCenter(),true);
}
void Scate::jump() {
	if(m_contacting)
		m_body->ApplyLinearImpulse(b2Vec2(0, -10), m_body->GetWorldCenter(), true);
}
//void Scate::move(sf::Clock& clock) {
//	float x = 0, y = 0;;
//
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
//		x = 4;
//	}
//	if (int(clock.getElapsedTime().asSeconds())%2==0 && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
//		y = -10;
//		clock.restart();
//	}
//	m_body->SetLinearVelocity(b2Vec2(x, y));
//}

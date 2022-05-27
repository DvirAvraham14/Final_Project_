#include"Scate.h"


void Scate::drive() {
	b2Vec2 vel = m_body->GetLinearVelocity();
	float desiredVel = 5;
	float velChange = desiredVel - vel.x;
	float force = m_body->GetMass() * velChange / (1 / 60.0); //disregard time factor
	m_body->ApplyForce(b2Vec2(force, 0), m_body->GetWorldCenter(), true);
}

void Scate::jump() {
	if (m_contacting) {
		m_body->ApplyLinearImpulse(b2Vec2(0, -15), m_body->GetWorldCenter(), true);
		m_contacting = false;
	}
}


void Scate::draw(sf::RenderWindow& target)  {
	b2Vec2 position = m_body->GetPosition();
	position *= SCALAR;
	float angle = 180 / b2_pi * m_body->GetAngle();
	m_sprite.setPosition(position.x, position.y);
	m_sprite.setRotation(angle);
	target.draw(m_sprite);
}


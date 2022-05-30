#include"Scate.h"


float Scate::physicalMove(float vel, float desiredVel) {
	float velChange = desiredVel - vel;
	return m_body->GetMass() * velChange; //disregard time factor
}

void Scate::drive() {

	if (m_contacting) {
		float impulse = physicalMove(m_body->GetLinearVelocity().x, 40);
		m_body->ApplyLinearImpulse(b2Vec2(impulse, 0), m_body->GetWorldCenter(), true);
	}
}

void Scate::jump() {

	if (m_contacting) {
		b2Vec2 vel = m_body->GetLinearVelocity();
		float impulse = physicalMove(vel.y, 50);
		m_body->ApplyLinearImpulse(b2Vec2(vel.x, -impulse), m_body->GetWorldCenter(), true);
		m_contacting = false;
	}
}


void Scate::draw(sf::RenderWindow& target) const {
	target.draw(m_sprite);
}


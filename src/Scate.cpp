#include"Scate.h"


float Scate::physicalMove(float vel, float desiredVel) {
	float velChange = desiredVel - vel;
	return m_body->GetMass() * ((velChange > desiredVel)?  desiredVel : velChange) / (1 / 60.0); //disregard time factor
}

void Scate::drive(int speed) {

	if (m_contacting) {
		float force = physicalMove(m_body->GetLinearVelocity().x, speed);
		m_body->ApplyForce(b2Vec2(force, 0), m_body->GetWorldCenter(), true);
	}
}

void Scate::jump() {

	if (m_contacting) {
		b2Vec2 vel = m_body->GetLinearVelocity();
		float force = physicalMove(vel.y, 40);
		m_body->ApplyForce(b2Vec2(vel.x, -force), m_body->GetWorldCenter(), true);
		endContact();
	}
}

//
//void Scate::draw(sf::RenderWindow& target) const {
//	target.draw(m_sprite);
//}
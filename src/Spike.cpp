#include "Spike.h"


void Spike::drive() {

	if (m_contacting) {
		m_speed += (m_speed < MAX_SPEED_SKATE) ? 5 : 0;
		float force = physicalMove(m_body->GetLinearVelocity().x, m_speed);
		m_body->ApplyForce(b2Vec2(force, 0), m_body->GetWorldCenter(), true);
	}
}

void Spike::jump(float height) {

	if (m_contacting) {
		m_animation.direction((m_dir = Direction::Filp));
		b2Vec2 vel = m_body->GetLinearVelocity();
		float force = physicalMove(vel.y, height);
		m_body->ApplyForce(b2Vec2(0, -force), m_body->GetWorldCenter(), true);
		endContact();
	}
}
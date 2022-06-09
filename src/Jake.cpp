#include "Jake.h"


void Jake::drive() {

	if (m_contacting) {
		m_speed += (m_speed < MAX_SPEED[Resources::Players::Jake]) ? 5 : 0;
		float force = physicalMove(m_body->GetLinearVelocity().x, m_speed);
		m_body->ApplyForce(b2Vec2(force, 0), m_body->GetWorldCenter(), true);
	}
}

void Jake::jump(float height) {

	if (m_contacting) {
		m_animation.direction(Direction::Filp);
		b2Vec2 vel = m_body->GetLinearVelocity();
		float force = physicalMove(vel.y, JUMP_HEIGHT[Resources::Players::Jake]);
		m_body->ApplyForce(b2Vec2(0, -force), m_body->GetWorldCenter(), true);
		endContact();
	}
}
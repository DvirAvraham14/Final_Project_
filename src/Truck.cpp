#include"Truck.h"

Truck::Truck(Resources::TEXTURE texture, std::shared_ptr<b2World> world, sf::Vector2f pos, Resources::Players aniData, Resources::SOUNDS sound)
	:Enemy(texture, world, pos, aniData,sound)
{
	auto size = m_sprite.getGlobalBounds();
	m_sprite.setOrigin(size.width/2, size.height/2);
	
}

void Truck::update(sf::Time time) {
	drive(20);
	b2Vec2  position = m_body->GetPosition();
	float	angle = 180 / b2_pi * m_body->GetAngle();
	m_sprite.setPosition(position.x, position.y);
	m_sprite.setRotation(angle);
}

void Truck::drive(int speed) {
	float force = physicalMove(m_body->GetLinearVelocity().x, speed);
	m_body->ApplyForce(b2Vec2(force, 0), m_body->GetWorldCenter(), true);
}

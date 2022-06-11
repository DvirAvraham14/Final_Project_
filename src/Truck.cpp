#include"Truck.h"

Truck::Truck(Resources::TEXTURE texture, std::shared_ptr<b2World> world, sf::Vector2f pos, Resources::Players aniData, Resources::SOUNDS sound)
	:Enemy(texture, world, pos, aniData, sound)
{
	auto size = m_sprite.getTextureRect();
	m_sprite.setOrigin(size.width / 2, size.height / 2 );

}

void Truck::update(sf::Time time) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		m_drive = true;
	if (m_drive) 
		drive(Resources::Players::P_Truck);
	b2Vec2  position = m_body->GetPosition();
	float	angle = 180 / b2_pi * m_body->GetAngle();
	m_sprite.setPosition(position.x, position.y);
	m_sprite.setRotation(angle);
	m_animation.update(time);
}

void Truck::drive(Resources::Players player) {
	if (m_enableMove) {
		m_speed += (m_speed < MAX_SPEED[player]) ? 5 : 0;
		float force = physicalMove(m_body->GetLinearVelocity().x, m_speed);
		m_body->ApplyForce(b2Vec2(force, 0), m_body->GetWorldCenter(), true);
	}
}

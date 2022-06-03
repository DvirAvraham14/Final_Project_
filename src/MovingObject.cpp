#include"MovingObject.h"

MovingObject::MovingObject( Resources::TEXTURE texture,
							std::shared_ptr<b2World> world,
							sf::Vector2f pos,
							Resources::Players aniData)
	:GameObject(texture, world, pos),
	m_speed(10),
	m_dir(Direction::Win),
	m_animation(Resources::instance().getData(aniData), Direction::Win, m_sprite)
	{
	}

void MovingObject::update(sf::Time delta) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		jump();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		drive();
	
	b2Vec2  position = m_body->GetPosition();
	float	angle = 180 / b2_pi * m_body->GetAngle();
	m_sprite.setPosition(position.x, position.y);
	m_sprite.setRotation(angle);
	m_animation.update(delta);
}

void MovingObject::changeAni() {
	m_dir = static_cast<Direction>((m_dir + 1) % Direction::MaxDir);
	m_animation.direction(m_dir);
}
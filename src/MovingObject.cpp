#include"MovingObject.h"

MovingObject::MovingObject(Resources::TEXTURE texture,
	std::shared_ptr<b2World> world,
	sf::Vector2f pos,
	Resources::Players aniData,
	Resources::SOUNDS sound)
	:GameObject(texture, world, pos, sound),
	m_dir(Direction::Win),
	m_animation(Resources::instance().getData(aniData), Direction::Win, m_sprite)
{}

void MovingObject::changeAni() {
	m_dir = static_cast<Direction>((m_dir + 1) % Direction::MaxDir);
	m_animation.direction(m_dir);
}
float MovingObject::physicalMove(float vel, float desiredVel) {
	float velChange = desiredVel - vel;
	return m_body->GetMass() * ((velChange > desiredVel) ? desiredVel : velChange) / (1 / 60.0); //disregard time factor
}
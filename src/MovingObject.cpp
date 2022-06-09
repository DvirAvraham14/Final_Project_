#include"MovingObject.h"

MovingObject::MovingObject(Resources::TEXTURE texture,
	std::shared_ptr<b2World> world,
	sf::Vector2f pos,
	Resources::Players aniData,
	Resources::SOUNDS sound)
	:GameObject(texture, world, pos, sound),
	m_animation(Resources::instance().getData(aniData), Direction::Start, m_sprite)
{
	m_sprite.setScale(WIDTH_WINDOW / 1137.f, WIDTH_WINDOW / 1137.f);
}


float MovingObject::physicalMove(float vel, float desiredVel) {
	float velChange = desiredVel - vel;
	return m_body->GetMass() * ((velChange > desiredVel) ? desiredVel : velChange) / (1 / 60.0); //disregard time factor
}
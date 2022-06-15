#include"EndFlag.h"

//___________________________________________________

EndFlag::EndFlag(Resources::TEXTURE texture,
	std::shared_ptr<b2World> world,
	sf::Vector2f pos,
	Resources::SOUNDS sound)
	:StaticObject(world, texture, pos, Resources::SOUNDS::Coins),
	m_animation(Resources::instance().getData(Resources::Players::P_FLAG), Direction::Drive, m_sprite)
{
	m_sprite.setPosition(pos);
	CreateBody(pos);
}

//___________________________________________________

void EndFlag::update(sf::Time delta) {

	m_animation.update(delta);
}


#pragma once
#include "Coin.h"

Coin::Coin(Resources::TEXTURE texture,
	std::shared_ptr<b2World> world,
	sf::Vector2f pos,
	Resources::SOUNDS sound)
	:StaticObject(world, texture,pos,Resources::SOUNDS::Coins),
	m_animation(Resources::instance().getData(Resources::Players::P_COIN),Direction::Drive, m_sprite)
{
	m_sprite.setOrigin(m_sprite.getTextureRect().width / 2.f, m_sprite.getTextureRect().height / 2.f);
	m_sprite.setPosition(sf::Vector2f(pos.x, pos.y - m_sprite.getOrigin().y));
	CreateBody(pos);

	undoCollision();
}

void Coin::update(sf::Time delta) {

	m_animation.update(delta);
}

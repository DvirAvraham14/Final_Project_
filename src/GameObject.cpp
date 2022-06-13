#include"GameObject.h"

GameObject::GameObject(Resources::TEXTURE textue,
	std::shared_ptr<b2World> world,
	sf::Vector2f pos,
	Resources::SOUNDS sound)
	:m_world(world),
	m_sprite(Resources::instance().getTexture(textue)),
	m_contacting(false)
{
	m_sound.setBuffer(Resources::instance().getSound(sound));
}

GameObject::GameObject(std::shared_ptr<b2World> world)
	:m_world(world),
	m_body(nullptr),
	m_contacting(false)
{}

void GameObject::draw(sf::RenderWindow& target) const {
	target.draw(m_sprite);
}
void GameObject::undoCollision() {
	for (auto it = m_body->GetFixtureList(); it; it = it->GetNext()) {
		if (it)
			it->SetSensor(true);
	}
}

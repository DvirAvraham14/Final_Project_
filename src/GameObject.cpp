#include"GameObject.h"
GameObject::GameObject(sf::Texture texture) {
	sf::Sprite s;
	m_texture = texture;
	s.setTexture(m_texture);
	m_sprite = s;
}
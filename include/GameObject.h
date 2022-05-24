#pragma once
#include "macro.h"
class GameObject
{
public:
	GameObject(sf::Texture texture);
	virtual void draw(sf::RenderWindow& target)=0;
protected:
	sf::Sprite m_sprite;
	sf::Texture m_texture;
private:
	
};
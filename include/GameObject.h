#pragma once
#include "macro.h"
class GameObject
{
public:
	GameObject(sf::Texture texture, std::shared_ptr<b2World>,sf::Vector2f pos);
	virtual void draw(sf::RenderWindow& target)=0;
	sf::Vector2f getPos() { return m_sprite.getPosition(); }
	void startContact() { m_contacting = true; }
	void endContact() { m_contacting = false; }
	
protected:
	sf::Sprite				 m_sprite;
	sf::Texture				 m_texture;
	std::shared_ptr<b2World> m_world;
	b2BodyDef				 m_bodyDef;
	b2Body*					 m_body;
	bool m_contacting = true;
private:
	
	void CreateBody(sf::Vector2f pos);
};
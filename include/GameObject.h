#pragma once
#include "macro.h"
class GameObject
{
public:
	GameObject(sf::Texture texture, std::shared_ptr<b2World>);
	virtual void draw(sf::RenderWindow& target)=0;
protected:
	sf::Sprite				 m_sprite;
	sf::Texture				 m_texture;
	std::shared_ptr<b2World> m_world;
	b2BodyDef				 m_bodyDef;
	b2Body*					 m_body;
private:
	
	void CreateBody();
};
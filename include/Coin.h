#pragma once
#include"StaticObject.h"
class Coin :public StaticObject
{
public:
	using StaticObject::StaticObject;
	Coin(Resources::TEXTURE, std::shared_ptr<b2World> world, sf::Vector2f pos, Resources::SOUNDS sound);
	~Coin() = default;
	void update(sf::Time);
	//	StaticObject()=default;
	//virtual void draw(sf::RenderWindow& target) const;
protected:

private:
	Animation m_animation;
};
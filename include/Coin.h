#pragma once
#include"StaticObject.h"
class Coin :public StaticObject
{
public:
	using StaticObject::StaticObject;
	~Coin() = default;
	//	StaticObject()=default;
	//virtual void draw(sf::RenderWindow& target) const;
protected:

private:

};
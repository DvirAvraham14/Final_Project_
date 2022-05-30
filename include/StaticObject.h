#pragma once
#include"GameObject.h"
class StaticObject :public GameObject
{
public:
	using GameObject::GameObject;
	//	StaticObject()=default;
	virtual void draw(sf::RenderWindow& target) const = 0;

protected:
	
private:
	float m_speed;
};
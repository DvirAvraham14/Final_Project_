#pragma once
#include"GameObject.h"
class MovingObject :public GameObject
{
public:
	using GameObject::GameObject;
	//MovingObject()=default;
	virtual void draw(sf::RenderWindow& target) =0;
	//virtual void draw(sf::RenderWindow& target) const;
	virtual void drive() = 0;
	virtual void jump() = 0;
	
	
	//Ball class functions
	
	
protected:
	
private:
	float m_speed;
};
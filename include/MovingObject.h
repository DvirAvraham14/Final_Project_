#pragma once
#include"GameObject.h"
class MovingObject :public GameObject
{
public:
	using GameObject::GameObject;
	virtual void draw(sf::RenderWindow& target) const = 0;
	//virtual void draw(sf::RenderWindow& target) const;
	virtual void drive()	= 0;
	virtual void jump()		= 0;
	void update();
	
protected:
	
private:
	float m_speed;
};
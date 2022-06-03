#pragma once
#include"GameObject.h"
#include "Animation.h"
class MovingObject :public GameObject
{
public:
	using GameObject::GameObject;
	MovingObject(Resources::TEXTURE, std::shared_ptr<b2World>, sf::Vector2f, Resources::Players aniData);
	virtual void drive(int = 60)			  = 0;
	virtual void jump(int = 40)				  = 0;
	virtual void CreateBody(sf::Vector2f pos) = 0;
	void update(sf::Time);
	void changeAni();
	
protected:
	Animation m_animation;
	Direction m_dir;
private:
	float m_speed;
};
#pragma once
#include"GameObject.h"
#include "Animation.h"
class MovingObject :public GameObject
{
public:
	using GameObject::GameObject;
	MovingObject(Resources::TEXTURE, std::shared_ptr<b2World>, sf::Vector2f, Resources::Players aniData,Resources::SOUNDS sound);
	virtual void drive(int=40)				  = 0;
	virtual void jump(int = 50)				  = 0;
	virtual void CreateBody(sf::Vector2f pos) = 0;
	virtual void update(sf::Time)			  = 0;
	void changeAni();
	float physicalMove(float vel, float desiredVel);
protected:
	Animation m_animation;
	Direction m_dir;
private:
	float m_speed;
};
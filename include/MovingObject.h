#pragma once
#include"GameObject.h"
#include "Animation.h"
class MovingObject :public GameObject
{
public:
	using GameObject::GameObject;
	MovingObject(Resources::TEXTURE, std::shared_ptr<b2World>, sf::Vector2f, Resources::Players aniData,Resources::SOUNDS sound);
	virtual void drive()						= 0;
	virtual void jump(float = JUMP_HEIGHT)		= 0;
	virtual void CreateBody(sf::Vector2f pos)	= 0;
	virtual void update(sf::Time)				= 0;
	inline void setSpeet(float speed) { m_speed = speed; }
	void changeAni();
	float physicalMove(float vel, float desiredVel);
	virtual inline void setRotate(bool set) { m_body->SetFixedRotation(set); }
	void setEnableMove(bool moveSatuse) { m_enableMove = moveSatuse; }
protected:
	bool m_enableMove = true;
	Animation m_animation;
	Direction m_dir;
	float m_speed = 0;
private:

};
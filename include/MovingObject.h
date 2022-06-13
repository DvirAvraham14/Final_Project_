#pragma once
#include"GameObject.h"
#include "Animation.h"
class MovingObject :public GameObject
{
public:
	using GameObject::GameObject;
	MovingObject(Resources::TEXTURE, std::shared_ptr<b2World>, sf::Vector2f, Resources::Players aniData,Resources::SOUNDS sound);
	virtual void drive(Resources::Players player) = 0;
	virtual void jump(float = 0, Resources::Players = Resources::Players::MaxPlayer) = 0;
	virtual void CreateBody(sf::Vector2f pos) = 0;
	inline void setSpeet(float speed) { m_speed = speed; }
	inline void setAni(Direction dir) { m_animation.direction(dir); }
	float physicalMove(float vel, float desiredVel);
	virtual inline void setRotate(bool set) { m_body->SetFixedRotation(set); }
	void setEnableMove(bool moveSatuse) { m_enableMove = moveSatuse; }
	void setBox2dEnable(bool value) { m_body->SetEnabled(value); }
	void setScreen() { Btn::setScreen(T_Screen::SCORE); }
	void setEnd(bool end) { m_endLevel = end; }
	bool getIsEnd() { return m_endLevel; }
protected:
	bool m_endLevel = false;
	bool m_enableMove = true;
	Animation m_animation;
	float m_speed = 0;
private:

};
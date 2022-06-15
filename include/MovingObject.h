#pragma once

#include"GameObject.h"
#include "Animation.h"

class MovingObject :public GameObject
{
public:
	using GameObject::GameObject;
	MovingObject(Resources::TEXTURE, std::shared_ptr<b2World>, sf::Vector2f, Resources::Players aniData, Resources::SOUNDS sound);
	virtual void drive(Resources::Players player) = 0;
	virtual void jump(float = 0, Resources::Players = Resources::Players::MaxPlayer) = 0;
	virtual void CreateBody(sf::Vector2f pos) = 0;
	//virtual void update(sf::Time)				;
	inline void setSpeet(float speed) { m_speed = speed; }
	inline void setAni(Direction dir) { m_animation.direction(dir); }
	float physicalMove(float vel, float desiredVel);
	void selVelocityZero() { m_body->SetLinearVelocity({ 0,0 }); }
	virtual inline void setRotate(bool set) { m_body->SetFixedRotation(set); }
	void setPosition(sf::Vector2f pos) { m_body->SetTransform(b2Vec2(pos.x, pos.y), 0); }
	void setEnableMove(bool moveSatuse) { m_enableMove = moveSatuse; }
	void setBox2dEnable(bool value) { m_body->SetEnabled(value); }
	void setEnd(bool end) { m_isEnd = end; }
	inline void setIsDead(bool life) { m_isDead = life; }
	inline bool isDead() const { return m_isDead; }
	inline bool getIsEnd()const { return m_isEnd; }

protected:
	bool       m_enableMove = true;
	Animation  m_animation;
	float      m_speed = 0;
	bool       m_isDead = false;

private:
	bool       m_isEnd = false;
};
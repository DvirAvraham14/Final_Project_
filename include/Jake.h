#pragma once
#include "PlayerVehicles.h"
class Jake : public PlayerVehicles
{
public:
	using PlayerVehicles::PlayerVehicles;
	//Scate() = default;

	//virtual void draw(sf::RenderWindow& target) const;
	virtual void drive();
	virtual void jump(float = JUMP_HEIGHT);
	void setAni(Direction dir) { m_animation.direction(dir); }
	//float physicalMove(float , float );
private:
};
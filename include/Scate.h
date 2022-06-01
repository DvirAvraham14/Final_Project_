#pragma once
#include "PlayerVehicles.h"
class Scate : public PlayerVehicles
{
public:
	using PlayerVehicles::PlayerVehicles;
	//Scate() = default;
	
	//virtual void draw(sf::RenderWindow& target) const;
	virtual void jump();
	virtual void drive(int speed=60);
	float physicalMove(float vel, float desiredVel);
private:
};
#pragma once
#include "PlayerVehicles.h"
class Scate : public PlayerVehicles
{
public:
	using PlayerVehicles::PlayerVehicles;
	//Scate() = default;
	
	//virtual void draw(sf::RenderWindow& target) const;
	virtual void jump(int);
	virtual void drive(int);
	float physicalMove(float , float );
private:
};
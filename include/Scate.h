#pragma once
#include "PlayerVehicles.h"
class Scate : public PlayerVehicles
{
public:
	using PlayerVehicles::PlayerVehicles;
	//Scate() = default;
	
	//virtual void draw(sf::RenderWindow& target) const;
	virtual void drive(int=40);
	virtual void jump(int=40);
	//float physicalMove(float , float );
private:
};
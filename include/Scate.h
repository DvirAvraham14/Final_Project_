#pragma once
#include "PlayerVehicles.h"
class Scate : public PlayerVehicles
{
public:
	using PlayerVehicles::PlayerVehicles;
	//Scate() = default;
	
	virtual void draw(sf::RenderWindow& target) ;
	virtual void jump();
	virtual void drive();

private:
};
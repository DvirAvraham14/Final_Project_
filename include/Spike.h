#pragma once
#include "PlayerVehicles.h"
class Spike : public PlayerVehicles
{
public:
	using PlayerVehicles::PlayerVehicles;
	//Scate() = default;
	
	//virtual void draw(sf::RenderWindow& target) const;
	virtual void drive(Resources::Players = Resources::Players::Jake);
	virtual void jump(float = 0,Resources::Players = Resources::Players::Spike);
	//float physicalMove(float , float );
private:
};
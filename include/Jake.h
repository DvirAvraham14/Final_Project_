#pragma once
#include "PlayerVehicles.h"
class Jake : public PlayerVehicles
{
public:
	using PlayerVehicles::PlayerVehicles;
	//Scate() = default;

	//virtual void draw(sf::RenderWindow& target) const;
	virtual void drive();
	virtual void jump(float = 0);


private:
};
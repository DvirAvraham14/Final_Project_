#pragma once
#include "PlayerVehicles.h"
class Tricky : public PlayerVehicles
{
public:
	using PlayerVehicles::PlayerVehicles;
	//Scate() = default;

	//virtual void draw(sf::RenderWindow& target) const;
	virtual void drive();
	virtual void jump(float = 0);

	//float physicalMove(float , float );
private:
};
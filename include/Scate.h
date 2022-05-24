#pragma once
#include "PlayerVehicles.h"
class Scate : public PlayerVehicles
{
public:
	using PlayerVehicles::PlayerVehicles;
	//Scate() = default;
	
	virtual void draw(sf::RenderWindow& target) override;
	virtual void jump()override;
	virtual void drive()override;

private:
};
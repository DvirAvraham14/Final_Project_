#pragma once
#include "MovingObject.h"
class PlayerVehicles : public MovingObject
{
public:
	using MovingObject::MovingObject;
	//PlayerVehicles() = default;
	//virtual void jump();
	//virtual void drive();
	virtual void draw(sf::RenderWindow& target) =0;

private:

};
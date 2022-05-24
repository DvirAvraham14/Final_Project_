#pragma once
#include "MovingObject.h"
class PlayerVehicles : public MovingObject
{
public:
	using MovingObject::MovingObject;
	//PlayerVehicles() = default;
	virtual void drive()=0;
	virtual void jump()=0;
	virtual void draw(sf::RenderWindow& target) =0;

private:

};
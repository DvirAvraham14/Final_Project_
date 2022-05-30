#pragma once
#include "MovingObject.h"
class PlayerVehicles : public MovingObject
{
public:
	using MovingObject::MovingObject;

	virtual void drive()								= 0;
	virtual void jump()									= 0;
	virtual void draw(sf::RenderWindow& target) const	= 0;

private:

};
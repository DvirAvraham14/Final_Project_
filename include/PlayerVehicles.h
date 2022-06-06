#pragma once
#include "MovingObject.h"
class PlayerVehicles : public MovingObject
{
public:
	
	PlayerVehicles(Resources::TEXTURE, std::shared_ptr<b2World>, sf::Vector2f, Resources::Players aniData, Resources::SOUNDS sound);
	virtual void drive(int=30 )				        = 0;
	virtual void jump( int=40 )						= 0;
	virtual void update(sf::Time delta);
	virtual void CreateBody(sf::Vector2f pos);

private:
	void setSensor(float posXm, b2PolygonShape& poly, b2FixtureDef&, int id);
	void setMassa(float);
};
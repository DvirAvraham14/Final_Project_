#pragma once
#include "MovingObject.h"
class PlayerVehicles : public MovingObject
{
public:
	
	PlayerVehicles(const sf::Texture& texture, std::shared_ptr<b2World> world, sf::Vector2f pos);
	virtual void drive(int speed = 60)				    = 0;
	virtual void jump()									= 0;
	//virtual void draw(sf::RenderWindow& target) const;
	virtual void CreateBody(sf::Vector2f pos);

private:
	void setSensor(float posXm, b2PolygonShape& poly, b2FixtureDef&, int id);
	void setMassa(float);
};
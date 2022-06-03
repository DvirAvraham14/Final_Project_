#pragma once
#include "MovingObject.h"
class PlayerVehicles : public MovingObject
{
public:
	
	//PlayerVehicles(const sf::Texture& texture, std::shared_ptr<b2World> world, sf::Vector2f pos);
	PlayerVehicles(Resources::TEXTURE, std::shared_ptr<b2World>, sf::Vector2f, Resources::Players aniData);
	virtual void drive(int )				    = 0;
	virtual void jump(int )						= 0;
	//virtual void draw(sf::RenderWindow& target) const;
	virtual void CreateBody(sf::Vector2f pos);

private:
	void setSensor(float posXm, b2PolygonShape& poly, b2FixtureDef&, int id);
	void setMassa(float);
};
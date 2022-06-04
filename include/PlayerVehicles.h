#pragma once
#include "MovingObject.h"
class PlayerVehicles : public MovingObject
{
public:
	
	//PlayerVehicles(const sf::Texture& texture, std::shared_ptr<b2World> world, sf::Vector2f pos);
	PlayerVehicles(Resources::TEXTURE, std::shared_ptr<b2World>, sf::Vector2f, Resources::Players aniData, Resources::SOUNDS sound);
	virtual void drive(int=40 )				        = 0;
	virtual void jump(int=40 )						= 0;
	virtual void update(sf::Time delta);
	//virtual void draw(sf::RenderWindow& target) const;
	virtual void CreateBody(sf::Vector2f pos);

private:
	void setSensor(float posXm, b2PolygonShape& poly, b2FixtureDef&, int id);
	void setMassa(float);
};
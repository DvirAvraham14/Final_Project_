#pragma once
#include "Obstacles.h"

class Spikes :public Obstacles
{
public:
	//using Obstacles::Obstacles;
	Spikes(Resources::TEXTURE texture, std::shared_ptr<b2World> world, sf::Vector2f pos, Resources::SOUNDS sound,bool = true);

private:
	void CreateBody(sf::Vector2f pos);
	void setSensor(float posXm, b2PolygonShape& poly, b2FixtureDef&, int id);
};
#pragma once

#include "StaticObject.h"

class Ground :public StaticObject
{
public:
	Ground(sf::ConvexShape road, std::shared_ptr<b2World> world);
	virtual void draw(sf::RenderWindow& target) const;
	void CreateGround();
	int getEndPoint() const ;

private:
	sf::ConvexShape m_road;
};
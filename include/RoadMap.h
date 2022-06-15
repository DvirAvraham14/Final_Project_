#pragma once

#include "Screen.h"

class RoadMap:public Screen
{
public:
	RoadMap();
	virtual void draw(sf::RenderWindow& target) const;
	virtual void handleMouse(sf::Event event, const sf::Vector2f cursorPos);
	virtual void handleScreen();
	void Unlock(int index);

private:
	void setLock();
};
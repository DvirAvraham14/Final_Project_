#pragma once

#include"Screen.h"

class RoadMap:public Screen
{
public:
	RoadMap();
	virtual void draw(sf::RenderWindow& target) const;
	virtual void handleScreen(sf::Event event, const sf::Vector2f cursorPos);
	void Unlock(int index);
private:
	void lockLevels();
	void setLock(std::vector<sf::Vector2f> position);
	std::vector<Btn> m_locks;
};
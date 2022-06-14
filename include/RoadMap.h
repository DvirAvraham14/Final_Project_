#pragma once

#include "Screen.h"
#include "GameScreen.h"

class RoadMap:public Screen
{
public:
	RoadMap();
	virtual void draw(sf::RenderWindow& target) const;
	virtual void handleMouse(sf::Event event, const sf::Vector2f cursorPos);
	virtual void handleScreen();
	void Unlock(int index);
private:
	bool      m_firstRound = true;
	sf::Sound m_sound;
	void lockLevels();
	void setLock(std::vector<sf::Vector2f> position);
};
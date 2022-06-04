#pragma once

#include"Screen.h"
#include"MovingObject.h"

class SelectVehicle :public Screen
{
public:
	SelectVehicle();
	virtual void draw(sf::RenderWindow& target) const;
	int static currPlayer;
	int static getScreen() { return currPlayer; };
private:
	void creatPlayers();
	void createButtons();
	void updateRect();
	std::vector<sf::IntRect> m_playerName;
	sf::Sprite               m_names;
};
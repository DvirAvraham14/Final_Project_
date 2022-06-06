#pragma once

#include"Screen.h"
#include "Animation.h"

class SelectVehicle :public Screen
{
public:
	SelectVehicle();
	virtual void draw(sf::RenderWindow& target) const;
	int static currPlayer;
	int static getScreen() { return currPlayer; };
private:
	using player = Resources::Players;
	T_Screen changePlayer(bool next);
	void creatPlayers();
	void createButtons();
	void updateRect();
	void update();
	std::vector<sf::IntRect> m_playerName;
	sf::Sprite               m_names;
	sf::Sprite				 m_player;
	sf::Clock				 m_gameClock;
	Animation				 m_ani;
};
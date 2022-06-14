#pragma once

#include"Screen.h"
#include "Animation.h"

class SelectVehicle :public Screen
{
public:
	SelectVehicle();
	virtual void draw(sf::RenderWindow& target) const;
	virtual void handleGame(sf::Time& delta);
	int static getPlayer() { return m_currPlayer; };
private:
	using player = Resources::Players;
	T_Screen changePlayer(bool next);
	void creatNameFrame();
	void creatPlayersName();
	void creatPlayers();
	void createButtons();
	void updateRect();
	int static               m_currPlayer;
	std::vector<sf::IntRect> m_playerName;
	sf::Sprite               m_names;
	sf::Sprite				 m_player;
	sf::Clock				 m_gameClock;
	Animation				 m_ani;
};
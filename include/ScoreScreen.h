#pragma once

#include "Screen.h"

class ScoreScreen :public Screen
{
public:
	ScoreScreen();
	virtual void draw(sf::RenderWindow& target) const;
	virtual void handleScreen();

private:
	void createButtons();
	void setStarsData();

	std::vector<sf::Sprite> m_stars;
	sf::Sound               m_sound;
	sf::Text                m_coinText;
	sf::Text                m_clockText;
};
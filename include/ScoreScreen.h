#pragma once

#include "Screen.h"
#include "GameScreen.h"

class ScoreScreen :public Screen
{
public:
	ScoreScreen();
	virtual void draw(sf::RenderWindow& target) const;
	virtual void handleScreen();
	void static setNumOfStars(int stars) { m_numOfStars = stars; }
private:
	int static m_numOfStars;
	void createButtons();
	void setStarsPos();
	void setStarsData(std::vector<sf::Vector2f> starsPos);
	std::vector<sf::Sprite> m_stars;
	sf::Sound               m_sound;
	sf::Text                m_coinText;
	sf::Text                m_clockText;
};
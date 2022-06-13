#pragma once

#include"Screen.h"

class ScoreScreen :public Screen
{
public:
	ScoreScreen();
	virtual void draw(sf::RenderWindow& target) const;
	void static setNumOfStars(int stars) { m_numOfStars = stars; }
private:
	int static m_numOfStars;
	void createButtons();
	void setStarsPos();
	void setStarsData(std::vector<sf::Vector2f> starsPos);
	std::vector<sf::Sprite> m_stars;
};
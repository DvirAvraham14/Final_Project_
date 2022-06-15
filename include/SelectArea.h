#pragma once

#include "Screen.h"

class SelectArea :public Screen
{
public:
	SelectArea();
	virtual void draw(sf::RenderWindow& target) const;

private:
	void creatBgs();
	void createButtons();
	void updateRect();

	std::vector<sf::Sprite>         m_Bg;
	std::vector<sf::IntRect>        m_BgName;
	sf::Sprite                      m_names;
	int                             m_currBg = NIGHT_CITY_BG;
};
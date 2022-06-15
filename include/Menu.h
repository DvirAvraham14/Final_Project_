#pragma once

#include "Screen.h"

class Menu:public Screen
{
public:
	Menu();
	virtual void draw(sf::RenderWindow& target) const;

private:
	void mute(int index);
	void createButtons();

	sf::Sprite					m_logo;
	sf::Listener				m_lis;
};
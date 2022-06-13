#pragma once

#include"Screen.h"

class Help :public Screen
{
public:
	Help();
	virtual void draw(sf::RenderWindow& target) const;
private:
	void createButtons();
	void updateSprite();

	bool m_firstScreen = true;
};
#pragma once
#include "Btn.h"
#include "Menu.h"

class Controller {
public:
	Controller();
	void run();
private:
	sf::Clock			m_gameClock;
	Btn					m_title;
	sf::RenderWindow	m_window;
	int					m_level = 1;

	void whilePlaying(sf::Event, sf::Vector2f );

	enum class Screen
	{
		Game,
	};

	Menu m_menu;
	Screen screen = Screen::Game;
};


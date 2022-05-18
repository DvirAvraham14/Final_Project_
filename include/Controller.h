#pragma once
#include "Menu.h"


class Controller {
public:
	Controller();
	void run();
private:
	sf::Clock					m_gameClock;
	Btn							m_title;
	sf::RenderWindow			m_window;
	int							m_level = 1;
	std::shared_ptr<Screen>		m_screen;

	void whilePlaying(sf::Event, sf::Vector2f );

	//enum class Screen
	//{
	//	Menu,
	//	Game,
	//};

	Menu m_menu;
	//Screen m_screen = Screen::Menu;
};


#pragma once
#include "Menu.h"
#include"GameObject.h"
#include"MovingObject.h"
#include "Scate.h"

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
	void createVehicels();


	Menu m_menu;
	Map m_map;
	std::vector<std::shared_ptr<MovingObject>> m_vehicels;
	//Screen m_screen = Screen::Menu;
};


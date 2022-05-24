#pragma once
#include "Menu.h"
#include"GameObject.h"
//#include"MovingObject.h"
#include "Scate.h"
#include"MangeLevel.h"
#include"MyContactListener.h"

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
	std::shared_ptr<b2World>	m_world = std::make_unique<b2World>(b2Vec2(0.0f, 10.0f));
	void updateLevel();
	void whilePlaying(sf::Event, sf::Vector2f );
	void createVehicels();
	bool m_nextLevel = true;
	Menu m_menu;
	Map m_map;
	std::vector<std::shared_ptr<MovingObject>> m_vehicels;
	ManageLevel m_manageLevel;

};


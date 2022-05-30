#pragma once
#include "Menu.h"
#include "Scate.h"
#include "Ground.h"
#include "Map.h"
#include "MangeLevel.h"
#include "MyContactListener.h"


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
	std::shared_ptr<b2World>	m_world = std::make_unique<b2World>(b2Vec2(0.0f, 9.8f));
	MyContactListener myContact;
	void updateLevel();
	void whilePlaying(sf::Event, sf::Vector2f );
	void createObj();
	bool m_nextLevel = true;
	Menu m_menu;
	Map m_map;
	std::vector<std::shared_ptr<MovingObject>> m_vehicels;
	std::vector<std::shared_ptr<GameObject>> m_objects;
	ManageLevel m_manageLevel;


};


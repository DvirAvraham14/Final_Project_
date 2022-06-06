#pragma once
#include "Menu.h"
#include "MyContactListener.h"
#include "DebugDraw.h"
#include "SelectVehicle.h"
#include "RoadMap.h"
#include "SelectArea.h"
#include "GameScreen.h"


class Controller {
public:
	Controller();
	void run();

private:
	Btn							             m_title;
	sf::RenderWindow			             m_window;
	std::vector<std::shared_ptr<Screen>>     m_screen;
	int                                      m_currScreen = 0;
	std::shared_ptr<sf::View>                m_view = std::make_shared<sf::View>();
	std::shared_ptr<b2World>                 m_world = std::make_shared<b2World>(b2Vec2(0.0f, 9.8f));
	MyContactListener                        myContact;
	void createScreens();
	bool m_nextLevel = true;
	



};


#pragma once
#include "Menu.h"
#include "MyContactListener.h"
#include "DebugDraw.h"
#include "SelectVehicle.h"
#include "RoadMap.h"
#include "SelectArea.h"
#include "GameScreen.h"
#include "ScoreScreen.h"
#include "Help.h"
#include <memory>


class Controller {
public:
	Controller();
	~Controller();
	void run();

private:
	Btn							             m_title;
	sf::RenderWindow			             m_window;
	std::vector<std::unique_ptr<Screen>>     m_screen;
	std::shared_ptr<sf::View>                m_view = std::make_shared<sf::View>();
	std::shared_ptr<b2World>                 m_world = std::make_shared<b2World>(b2Vec2(0.0f, 9.8f));
	MyContactListener                        myContact;
	sf::Clock					             m_gameClock;
	bool                                     m_nextLevel = true;

	void createScreens();
};


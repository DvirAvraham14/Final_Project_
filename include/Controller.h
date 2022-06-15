#pragma once
#include "Menu.h"
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
	~Controller() {};
	void run();

private:
	void createScreens();
	void setMusic();
	void checkCond();
	void handleFunctions();

	Btn							             m_title;
	sf::RenderWindow			             m_window;
	std::vector<std::unique_ptr<Screen>>     m_screen;
	std::shared_ptr<sf::View>                m_view = std::make_shared<sf::View>();
	sf::Clock					             m_gameClock;
	sf::Sound                                m_gameMusic;
};


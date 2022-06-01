#include "Controller.h"

Controller::Controller()
	:m_screen(std::make_shared<Screen>()), m_menu(m_screen)
{
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	m_window.create(sf::VideoMode(WIDTH_WINDOW, HEIGHT_WINDOW, desktop.bitsPerPixel),
		"Death Race",
		sf::Style::Titlebar | sf::Style::Close);
	m_view =sf::View(m_window.getDefaultView());
	m_world->SetContactListener(&myContact);
	updateLevel();
	createObj();
}

//__________________________________
void Controller::run() {
	sf::Vector2f cursorPosF;
	
	//auto delta = m_gameClock.restart();
	DebugDraw d(m_window);
	d.SetFlags(b2Draw::e_shapeBit | b2Draw::e_centerOfMassBit);
	m_world->SetDebugDraw(&d);
	while (m_window.isOpen()) {
		m_window.clear(sf::Color::White);
		m_window.setView(m_view);
		sf::Event event;
		cursorPosF = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
		while (m_window.pollEvent(event)) {

			switch (m_screen->getScreen())
			{
			//default:
			//	throw std::invalid_argument("Unknown enum entery used!");
			//	break;
			case T_Screen::Menu:			m_menu.handleMouse(event, cursorPosF);		break;
		//	case T_Screen::Game:			whilePlaying(event);						break;
			}
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				m_window.close();
		}
		if(m_screen->getScreen() == T_Screen::Game)
			updateGameMoves();

		draw();
		m_window.display();

		//if (m_screen->getScreen() == T_Screen::Menu) {
		//	m_menu.Draw(m_window);
		//}
		/*if (m_nextLevel)
			updateLevel();*/
	}
}


void Controller::updateLevel() {

	m_map.createMap(m_level);
	//m_nextLevel = false;
	//m_level++;
}


void Controller::createObj() {

	m_objects.push_back(std::make_shared<Ground>(m_level, m_map.getRoad(),m_world));
	m_vehicels.push_back(std::make_shared<Scate>(Resources::instance().getTexture(Resources::TEXTURE::SCATE), m_world, sf::Vector2f(200, 500)));

	std::vector<sf::Vector3f> obstacles = m_map.getObstacels();
	for (auto& obstacle : obstacles) {
		switch (int(obstacle.x)){
			case 1:
				m_objects.push_back(std::make_shared<Railing>(Resources::instance().getTexture(Resources::TEXTURE::RAILING), 
					m_world, sf::Vector2f(obstacle.y, obstacle.z)));
			break;
			case 2:
				m_objects.push_back(std::make_shared<Spikes>(Resources::instance().getTexture(Resources::TEXTURE::SPIKES),
					m_world, sf::Vector2f(obstacle.y, obstacle.z)));
				std::cout << obstacle.y << obstacle.z;
			break;
		}
	}
}



//void Controller::whilePlaying(sf::Event event) {
//	if (event.type == sf::Event::KeyPressed && m_screen->getScreen() == T_Screen::Game) {
//		m_manageLevel.manageAction(m_vehicels, event);
//	}
//}


void Controller::draw() {
	if(m_screen->getScreen() == T_Screen::Menu)
		m_menu.Draw(m_window);

	else if (m_screen->getScreen() == T_Screen::Game) {
		for (auto& obj : m_objects)
			obj->draw(m_window);
		m_vehicels[0]->draw(m_window);
		m_world->DebugDraw();
	}
}


void Controller::updateGameMoves() {
	if (static_cast<Ground*>(m_objects[0].get())->getEndPoint() - m_vehicels[0]->getPos().x > WIDTH_WINDOW)
		m_view.setCenter(sf::Vector2f(m_vehicels[0]->getPos().x + 350.0f, HEIGHT_WINDOW / 2));

	m_world->Step(timeStep, velocityIterations, positionIterations);
	m_vehicels[0]->update();
}


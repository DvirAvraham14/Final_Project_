#include "Controller.h"
#include "DebugDraw.h"

Controller::Controller()
	:m_screen(std::make_shared<Screen>()), m_menu(m_screen)
{
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	m_window.create(sf::VideoMode(WIDTH_WINDOW, HEIGHT_WINDOW, desktop.bitsPerPixel),
		"Death Race",
		sf::Style::Titlebar | sf::Style::Close);

	m_world->SetContactListener(&myContact);
	updateLevel();
	createObj();
}

//__________________________________
void Controller::run() {
	sf::Vector2f cursorPosF;
	sf::View   View(m_window.getDefaultView());
	//auto delta = m_gameClock.restart();
	DebugDraw d(m_window);
	d.SetFlags(b2Draw::e_shapeBit | b2Draw::e_centerOfMassBit);
	m_world->SetDebugDraw(&d);
	while (m_window.isOpen()) {
		m_window.clear(sf::Color::White);
		m_window.setView(View);
		sf::Event event;
		cursorPosF = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
		while (m_window.pollEvent(event)) {

			switch (m_screen->getScreen())
			{
			default:
				throw std::invalid_argument("Unknown enum entery used!");
				break;
			case T_Screen::Menu:			whilePlaying(event, cursorPosF);		break;
			case T_Screen::Game:			/*whilePlaying(event, cursorPosF);*/	break;
			}
			if (event.type == sf::Event::Closed)
				m_window.close();
			if (event.type == sf::Event::KeyPressed && m_screen->getScreen() == T_Screen::Game) {
				m_manageLevel.manageAction(m_vehicels, event);
			}
		}

		if (m_screen->getScreen() == T_Screen::Menu) {
			m_menu.Draw(m_window);
		}
		if (m_screen->getScreen() == T_Screen::Game) {
			if(static_cast<Ground*>( m_objects[0].get() )->getEndPoint() - m_vehicels[0]->getPos().x > WIDTH_WINDOW )
				View.setCenter(sf::Vector2f(m_vehicels[0]->getPos().x + 350.0f, HEIGHT_WINDOW/2));
			m_world->Step(timeStep, velocityIterations, positionIterations);
			m_objects[0]->draw(m_window);
			m_vehicels[0]->update();
			m_vehicels[0]->draw(m_window);
			m_world->DebugDraw();
		}
		/*if (m_nextLevel)
			updateLevel();*/
		
		m_window.display();
	}
}


void Controller::updateLevel() {

	m_map.createMap(m_level);
	//m_nextLevel = false;
	//m_level++;
}


void Controller::createObj() {

	m_objects.push_back(std::make_shared<Ground>(m_level, m_map.getRoad(),m_world));

	m_vehicels.push_back(std::make_shared<Scate>(Resources::instance().getTexture(Resources::TEXTURE::SCATE), m_world, sf::Vector2f(200, 450)));
}



void Controller::whilePlaying(sf::Event event, sf::Vector2f cursorPosF) {

	try {
		m_menu.handleMouse(event, cursorPosF);
	}
	catch (std::exception&) {}
}


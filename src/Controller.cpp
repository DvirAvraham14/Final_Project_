#include "Controller.h"

T_Screen Btn::m_screen			= T_Screen::MENU;
int SelectVehicle::currPlayer	= Resources::Players::Spike;

Controller::Controller()
{
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	m_window.create(sf::VideoMode(WIDTH_WINDOW, HEIGHT_WINDOW, desktop.bitsPerPixel),
		"Death Race",
		sf::Style::Titlebar | sf::Style::Close);
	*m_view =sf::View(m_window.getDefaultView());
	m_world->SetContactListener(&myContact);
	
	createScreens();
}

//__________________________________
void Controller::run() {
	sf::Vector2f cursorPosF;
	
	// debug draw
	DebugDraw d(m_window);
	d.SetFlags(b2Draw::e_shapeBit | b2Draw::e_centerOfMassBit);
	m_world->SetDebugDraw(&d);

	while (m_window.isOpen()) {
		m_currScreen = Btn::getScreen();
		m_window.clear(sf::Color::White);
		m_window.setView(*m_view);
		sf::Event event;
		cursorPosF = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
		while (m_window.pollEvent(event)) {
			if (m_currScreen != T_Screen::GAME)
				m_screen[m_currScreen]->handleScreen(event, cursorPosF);
			
			if (event.type == sf::Event::Closed || event.type == sf::Keyboard::Escape)
				m_window.close();
		}
		if (m_currScreen == T_Screen::GAME)
			m_screen[m_currScreen]->handleScreen(event, cursorPosF);

		m_screen[m_currScreen]->update();	
		m_screen[m_currScreen]->draw(m_window);
		m_world->DebugDraw();
		m_window.display();
	}
}

void Controller::createScreens() {
	m_screen.push_back(std::make_shared<Menu>());
	m_screen.push_back(std::make_shared<RoadMap>());
	m_screen.push_back(std::make_shared<SelectVehicle>());
	m_screen.push_back(std::make_shared<SelectArea>());
	m_screen.push_back(std::make_shared<GameScreen>(m_world, m_view));
}

#include "Controller.h"
#include "Resources.h"

Controller::Controller()
{
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	m_window.create(sf::VideoMode(WIDTH_WINDOW, HEIGHT_WINDOW, desktop.bitsPerPixel) , "Death Race");

	//m_window.create(sf::VideoMode, "Death Race", sf::Style::Titlebar | sf::Style::Close);
}

//__________________________________
void Controller::run() {
	sf::Vector2f cursorPosF;
	while (m_window.isOpen()) {
		m_window.clear(sf::Color::White);
		sf::Event event;
		cursorPosF = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
		while (m_window.pollEvent(event)) {
			switch (screen)
			{
			default:
				throw std::invalid_argument("Unknown enum entery used!");
				break;
			case Screen::Game:			whilePlaying(event, cursorPosF);	break;
			}
			if (event.type == sf::Event::Closed)
				m_window.close();
		}
		auto delta = m_gameClock.restart();
		if (screen == Screen::Game) {
			m_menu.Draw(m_window);
		}

		m_window.display();

	}
}


void Controller::whilePlaying(sf::Event event, sf::Vector2f cursorPosF) {

		try {
			m_menu.handleMouse(event, cursorPosF);
			
		}
		catch (std::exception& e) {
			
		}
}


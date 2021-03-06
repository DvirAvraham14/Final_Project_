#include "Controller.h"
#include "Resources.h"

Controller::Controller()
	:m_screen(std::make_shared<Screen>()), m_menu(m_screen)
{
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	m_window.create(sf::VideoMode(WIDTH_WINDOW, HEIGHT_WINDOW, desktop.bitsPerPixel) ,
		"Death Race",
		sf::Style::Titlebar | sf::Style::Close);
}

//__________________________________
void Controller::run() {
	sf::Vector2f cursorPosF;
	sf::View   View(m_window.getDefaultView());
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
			case T_Screen::Menu:			whilePlaying(event, cursorPosF);	break;
			case T_Screen::Game:			whilePlaying(event, cursorPosF);	break;
			}
			if (event.type == sf::Event::Closed)
				m_window.close();
		}
		auto delta = m_gameClock.restart();
	
		if (m_screen->getScreen() == T_Screen::Menu) {
			m_menu.Draw(m_window);
		}
		if (m_screen->getScreen() == T_Screen::Game) {
			View.move(0.f, -1.f); // negative y to move 'up' along sprite height
			m_map.draw(m_window);
		}
		m_window.display();
	}
}


void Controller::whilePlaying(sf::Event event, sf::Vector2f cursorPosF) {

		try {
			m_menu.handleMouse(event, cursorPosF);
		}
		catch (std::exception& ) {}
}


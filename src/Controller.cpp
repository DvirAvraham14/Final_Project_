#include "Controller.h"
#include "Resources.h"

Controller::Controller()
	:m_screen(std::make_shared<Screen>()), m_menu(m_screen)
{
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	m_window.create(sf::VideoMode(WIDTH_WINDOW, HEIGHT_WINDOW, desktop.bitsPerPixel) ,
		"Death Race",
		sf::Style::Titlebar | sf::Style::Close);
	createVehicels();
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
			if (event.type == sf::Event::KeyPressed && m_screen->getScreen()==T_Screen::Game)
				View.move(3.f, 0.f); 
		}
		auto delta = m_gameClock.restart();
	
		if (m_screen->getScreen() == T_Screen::Menu) {
			m_menu.Draw(m_window);
		}
		if (m_screen->getScreen() == T_Screen::Game) {
			m_map.draw(m_window);
			//m_vehicels[0]->draw(m_window);
		}
		m_window.display();
	}
}



void Controller::createVehicels() {
	m_vehicels.push_back(std::make_shared<Scate>(Resources::instance().getTexture(Resources::TEXTURE::SCATE)));
}



void Controller::whilePlaying(sf::Event event, sf::Vector2f cursorPosF) {

		try {
			m_menu.handleMouse(event, cursorPosF);
		}
		catch (std::exception& ) {}
}


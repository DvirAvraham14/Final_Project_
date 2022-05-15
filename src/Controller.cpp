#include "Controller.h"
#include "Resources.h"

Controller::Controller()
{
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	m_window.create(sf::VideoMode(1024, 768, desktop.bitsPerPixel), "SFML window");
	//m_window.create(sf::VideoMode, "Death Race", sf::Style::Titlebar | sf::Style::Close);
	m_title = Btn(winSize.x/2.f, winSize.y/3.f, " ", false, nullptr);
	m_title.fontSize(35);
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

		}
		auto delta = m_gameClock.restart();
		if (screen == Screen::Game) {
		}

		m_window.display();

	}
}


void Controller::whilePlaying(sf::Event event, sf::Vector2f cursorPosF) {

	switch (event.type) {
	case sf::Event::Closed:
		m_window.close();
		break;
	case sf::Event::MouseMoved:
		///mouse move
		break;
	case sf::Event::MouseButtonReleased:
		try {
			
			break;
		}
		catch (std::exception& e) {
			
		}
	}

}


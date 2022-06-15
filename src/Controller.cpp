#include "Controller.h"

Controller::Controller()
{
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	m_window.create(sf::VideoMode(WIDTH_WINDOW, HEIGHT_WINDOW, desktop.bitsPerPixel),
		"Death Race",
		sf::Style::Titlebar | sf::Style::Close);

	*m_view =sf::View(m_window.getDefaultView());
	
	createScreens();
	m_gameMusic.setBuffer(Resources::instance().getSound(Resources::GAME_MUSIC));
	m_gameMusic.setLoop(true);
	m_gameMusic.setVolume(70);
}

//__________________________________
void Controller::run() {
	sf::Vector2f cursorPosF;
	
	m_gameMusic.play();
	while (m_window.isOpen()) {
		try {
			
			if(GameData::instance().getScreen() ==SCORE)
				m_view->setCenter(m_window.getDefaultView().getCenter());
			if (GameData::instance().getScreen() == GAME)
				m_gameMusic.setVolume(20);
			else
				m_gameMusic.setVolume(70);
			m_window.clear(sf::Color::White);
			m_window.setView(*m_view);
			sf::Event event;
			cursorPosF = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));

			while (m_window.pollEvent(event)) {
				if (GameData::instance().getScreen() != T_Screen::GAME)
					m_screen[GameData::instance().getScreen()]->handleMouse(event, cursorPosF);

				if (event.type == sf::Event::Closed || (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))) {
					m_window.close();
				}
			}
			auto delta = m_gameClock.restart();
			m_screen[GameData::instance().getScreen()]->handleScreen();
			m_screen[GameData::instance().getScreen()]->handleGame(delta);
			m_screen[GameData::instance().getScreen()]->draw(m_window);
			m_window.display();
		}
		catch (std::exception& e) {
			std::cout << "Exp:\t" << e.what() << ".\n";
		}
	}
}

void Controller::createScreens() {

	m_screen.push_back(std::make_unique<Menu>());
	m_screen.push_back(std::make_unique<Help>());
	m_screen.push_back(std::make_unique<SelectVehicle>());
	m_screen.push_back(std::make_unique<SelectArea>());
	m_screen.push_back(std::make_unique<RoadMap>());
	m_screen.push_back(std::make_unique<ScoreScreen>());
	m_screen.push_back(std::make_unique<GameScreen>(m_view));
	
}
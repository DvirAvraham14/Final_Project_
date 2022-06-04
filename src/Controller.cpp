#include "Controller.h"
T_Screen Btn::m_screen = T_Screen::MENU;
int SelectVehicle::currPlayer = TRICKY;

Controller::Controller()
{
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	m_window.create(sf::VideoMode(WIDTH_WINDOW, HEIGHT_WINDOW, desktop.bitsPerPixel),
		"Death Race",
		sf::Style::Titlebar | sf::Style::Close);
	*m_view =sf::View(m_window.getDefaultView());
	m_world->SetContactListener(&myContact);
	
	createScreens();
	//m_window.setFramerateLimit(0);
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
			if (m_currScreen != GAME)
			m_screen[m_currScreen]->handleScreen(event, cursorPosF);
			
			if (event.type == sf::Event::Closed || event.type == sf::Keyboard::Escape)
				m_window.close();
		}
		if(m_currScreen==GAME)
			m_screen[m_currScreen]->handleScreen(event, cursorPosF);
		
			
		m_screen[m_currScreen]->draw(m_window);
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

/*#include "Controller.h"

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
	
	// debug draw
	DebugDraw d(m_window);
	d.SetFlags(b2Draw::e_shapeBit | b2Draw::e_centerOfMassBit);
	m_world->SetDebugDraw(&d);
	//end de

	while (m_window.isOpen()) {
		m_window.clear(sf::Color::White);
		m_window.setView(m_view);
		sf::Event event;
		cursorPosF = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
		while (m_window.pollEvent(event)) {

			switch (m_screen->getScreen())
			{
			default:
				//throw std::invalid_argument("Unknown enum entery used!");
				break;
			case T_Screen::Menu:			m_menu.handleMouse(event, cursorPosF);		break;
			case T_Screen::Game:
			{
				if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space)
					static_cast<MovingObject*>(m_vehicels[0].get())->changeAni();
				break;
			}
			}
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				m_window.close();
		}
		if(m_screen->getScreen() == T_Screen::Game)
			updateGameMoves();

		draw();
		m_window.display();

	}
}


void Controller::updateLevel() {

	m_map.createMap(m_level);
}



void Controller::createObj() {

	m_objects.push_back(std::make_shared<Ground>(m_level, m_map.getRoad(), m_world));
	m_vehicels.push_back(std::make_shared<Scate>(res::TEXTURE::SpikeTexture, m_world, sf::Vector2f(200, 500), res::Players::Spike));

	std::vector<sf::Vector3f> obstacles = m_map.getObstacels();
	for (auto& obstacle : obstacles) {
		switch (int(obstacle.x)) {
		case 1:
			m_objects.push_back(std::make_shared<Railing>(res::TEXTURE::RAILING, m_world, sf::Vector2f(obstacle.y, obstacle.z)));
			break;
		case 2:
			m_objects.push_back(std::make_shared<Spikes>(res::TEXTURE::SPIKES,
				m_world, sf::Vector2f(obstacle.y, obstacle.z)));
			break;
		case 3:
			m_objects.push_back(std::make_shared<EndFlag>(res::TEXTURE::Flag,
				m_world, sf::Vector2f(obstacle.y, obstacle.z)));
			break;
		case 4:
			m_enemies.push_back(std::make_shared<Monster>(Resources::TEXTURE::Monster,
				m_world, sf::Vector2f(obstacle.y, obstacle.z),
				Resources::Players::Enemy));
			break;

		}
	}
}

void Controller::draw() {
	if(m_screen->getScreen() == T_Screen::Menu)
		m_menu.Draw(m_window);

	else if (m_screen->getScreen() == T_Screen::Game) {
		for (auto& obj : m_objects)
			obj->draw(m_window);
		m_vehicels[0]->draw(m_window);
		m_enemies[0]->draw(m_window);
		m_world->DebugDraw();
	}
}


void Controller::updateGameMoves() {
	if (static_cast<Ground*>(m_objects[0].get())->getEndPoint() - m_vehicels[0]->getPos().x > WIDTH_WINDOW)
		m_view.setCenter(sf::Vector2f(m_vehicels[0]->getPos().x + 350.0f, HEIGHT_WINDOW / 2));

	m_world->Step(timeStep, velocityIterations, positionIterations);
	const auto delta = m_gameClock.restart();
	m_vehicels[0]->update(delta);
	m_enemies[0]->drive(7);
}*/

#include"RoadMap.h"

RoadMap::RoadMap() 
	:Screen(Resources::TEXTURE::MAP_ROAD, T_Screen::MENU)
{
	lockLevels();
	m_sound.setBuffer(Resources::instance().getSound(Resources::UNLOCK));
}

void RoadMap::lockLevels() {

	std::vector<sf::Vector2f> position;
	position.push_back({ WIDTH_WINDOW / 1.2f ,HEIGHT_WINDOW / 1.35f });
	position.push_back({ WIDTH_WINDOW / 1.435f, HEIGHT_WINDOW / 1.72f });
	position.push_back({ WIDTH_WINDOW / 1.335f, HEIGHT_WINDOW / 3.39f });
	position.push_back({ WIDTH_WINDOW / 1.56f, HEIGHT_WINDOW / 6.8f });
	position.push_back({ WIDTH_WINDOW / 1.915f, HEIGHT_WINDOW / 3.39f });
	position.push_back({ WIDTH_WINDOW / 2.09f, HEIGHT_WINDOW / 1.72f });
	position.push_back({ WIDTH_WINDOW / 2.6f, HEIGHT_WINDOW / 1.35f });
	position.push_back({ WIDTH_WINDOW / 3.2f, HEIGHT_WINDOW / 1.72f });
	position.push_back({ WIDTH_WINDOW / 2.79f, HEIGHT_WINDOW / 3.39f });
	position.push_back({ WIDTH_WINDOW / 4.2f, HEIGHT_WINDOW / 6.8f });
	position.push_back({ WIDTH_WINDOW / 7.6f, HEIGHT_WINDOW / 3.39f });

	setLock(position);
}

void RoadMap::setLock(std::vector<sf::Vector2f> position) {
	sf::Sprite lock;
	auto currScreen = SELECT_LEVEL;
	lock.setTexture(Resources::instance().getTexture(Resources::TEXTURE::LOCK));
	lock.setScale(WIDTH_WINDOW / 1420.0f, WIDTH_WINDOW / 1420.0f);
	for (auto& i : position) {
		m_buttons.push_back(Btn(i, lock));
	};
}

void RoadMap::Unlock(int index) {
	m_buttons[index].unlock([&]() ->T_Screen {return SELECT_VEHICLE; });
	this->setNextLevel(false);
}

void RoadMap::handleScreen(sf::Event event, const sf::Vector2f cursorPos) {
	for (auto& btn : m_buttons)
		if (event.type == sf::Event::MouseButtonReleased)
			btn.Press(cursorPos);
	if (this->getNextLevel()) {
		m_sound.play();
		Unlock(getLevel());
	}
}

int RoadMap::getLevel() {
	for (auto i = 1; i < m_buttons.size(); i++)
		if (m_buttons[i].isLock())
			return i;
}
void RoadMap::draw(sf::RenderWindow& target) const {
	Draw(target);
}

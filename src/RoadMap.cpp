#include"RoadMap.h"

//___________________________________________________

RoadMap::RoadMap() 
	:Screen(Resources::TEXTURE::MAP_ROAD, T_Screen::SELECT_AREA)
{
	setLock();
}

//___________________________________________________

void RoadMap::setLock() {
	sf::Sprite lock;
	auto currScreen = SELECT_LEVEL;
	lock.setTexture(Resources::instance().getTexture(Resources::TEXTURE::LOCK));
	lock.setScale(LOCK_SCALE);
	for (auto& i : LOCK_LEVEL) {
		m_buttons.push_back(Btn(i, lock));
	};
}

//___________________________________________________

void RoadMap::Unlock(int index) {

	for (auto i = LEVELS_BTN; i <= index; i++) {
		m_buttons[i].unlock(i);
	}
	GameData::instance().setIsNextLevel(false);
}

//___________________________________________________

void RoadMap::handleMouse(sf::Event event, const sf::Vector2f cursorPos) {
	for (auto i = 0; i < m_buttons.size(); i++) {
		if (event.type == sf::Event::MouseMoved) {
			if (i == BACK_BTN)
				m_buttons[i].hover(cursorPos);
			else {
				m_buttons[i].Mark(cursorPos);
			}
		}
		if (event.type == sf::Event::MouseButtonReleased) {
			if (i == BACK_BTN)
				m_buttons[i].Press(cursorPos);
			else
				m_buttons[i].chooseLevel(cursorPos);
		}
	}
}

//___________________________________________________

void RoadMap::handleScreen() {
	if (GameData::instance().getIsNextLevel()) {
		Unlock(GameData::instance().getLevel());
	}
}

//___________________________________________________

void RoadMap::draw(sf::RenderWindow& target) const {
	Draw(target);
}

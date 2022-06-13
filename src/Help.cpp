#include "Help.h"

Help::Help()
	:Screen(Resources::TEXTURE::HELP_CENTER1, T_Screen::MENU)
{
	createButtons();
}

void Help::createButtons() {

	sf::Sprite arrow;
	arrow.setTexture(Resources::instance().getTexture(Resources::TEXTURE::ARROW));
	arrow.setScale(WIDTH_WINDOW / 1420.0f, WIDTH_WINDOW / 1420.0f);

	m_buttons.push_back(Btn({ WIDTH_WINDOW / 27.0f,HEIGHT_WINDOW / 2.2f }, arrow,
		[&]() ->T_Screen { updateSprite(); return HELP; }));
	arrow.scale(-1, 1);

	m_buttons.push_back(Btn({ WIDTH_WINDOW / 1.025f,HEIGHT_WINDOW / 2.2f }, arrow,
		[&]() ->T_Screen { updateSprite(); return HELP; }));
}

void Help::updateSprite() {

	if (m_firstScreen) {
		m_background.setTexture(&Resources::instance().getTexture(Resources::TEXTURE::HELP_CENTER2));
		m_firstScreen = false;
	}
	else {
		m_background.setTexture(&Resources::instance().getTexture(Resources::TEXTURE::HELP_CENTER1));
		m_firstScreen = true;
	}
}

void Help::draw(sf::RenderWindow& target) const {

	Draw(target);
}
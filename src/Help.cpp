#include "Help.h"

//___________________________________________________

Help::Help()
	:Screen(Resources::TEXTURE::HELP_CENTER1, T_Screen::MENU)
{
	createButtons();
}

//___________________________________________________

void Help::createButtons() {

	sf::Sprite arrow;
	arrow.setTexture(Resources::instance().getTexture(Resources::TEXTURE::ARROW));
	arrow.setScale(ARROW_SCALE);

	m_buttons.push_back(Btn(ARROW_LEFT_POS, arrow,
		[&]() ->T_Screen { updateSprite(); return HELP; }));
	arrow.scale(MOVE_LEFT);

	m_buttons.push_back(Btn(ARROW_RIGHT_POS, arrow,
		[&]() ->T_Screen { updateSprite(); return HELP; }));
}

//___________________________________________________

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

//___________________________________________________

void Help::draw(sf::RenderWindow& target) const {

	Draw(target);
}
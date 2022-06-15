#include "Menu.h"

//___________________________________________________

Menu::Menu()
	:Screen(Resources::TEXTURE::BG, T_Screen::MENU)
{
	createButtons();

	m_buttons.erase(m_buttons.begin());
}

//___________________________________________________

void Menu::createButtons() {

	m_buttons.push_back(Btn(PLAY_POS.x, PLAY_POS.y, Resources::TEXTURE::PLAY,
		[&]()->T_Screen{return SELECT_VEHICLE; }));

	m_buttons.push_back(Btn(HELP_POS.x, HELP_POS.y, Resources::TEXTURE::HELP,[]()->T_Screen {return HELP; }));
	m_buttons.push_back(Btn(MUTE_POS.x, MUTE_POS.y, Resources::TEXTURE::SOUND, [&]()->T_Screen
		{ this->mute(m_buttons.size() - 1); return MENU; }));
}

//___________________________________________________

void Menu::mute(int index) {

	if (m_lis.getGlobalVolume() > MUTE) {
		m_lis.setGlobalVolume(MUTE);
		m_buttons[index].updateSprite(Resources::TEXTURE::MUTE);
	}
	else {
		m_lis.setGlobalVolume(VOLUME);
		m_buttons[index].updateSprite(Resources::TEXTURE::SOUND);
	}
}

//___________________________________________________

void Menu::draw(sf::RenderWindow& target) const {
	Draw(target);
}
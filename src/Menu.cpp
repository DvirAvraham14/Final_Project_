#include "Menu.h"

Menu::Menu()
	:Screen(Resources::TEXTURE::BG, T_Screen::MENU)
{
	createButtons();

	m_buttons.erase(m_buttons.begin());
	//logo
	m_logo.setTexture(Resources::instance().getTexture(Resources::TEXTURE::LOGO));
	m_logo.setOrigin(m_logo.getGlobalBounds().width / 2, m_logo.getGlobalBounds().height / 2);
	m_logo.setPosition(WIDTH_WINDOW / 2.f, HEIGHT_WINDOW / 1.17f);
	m_logo.setScale(WIDTH_WINDOW / 2000.f, WIDTH_WINDOW / 2000.f);
	
}

void Menu::createButtons() {

	m_buttons.push_back(Btn(WIDTH_WINDOW / 2.f, HEIGHT_WINDOW / 1.4f, Resources::TEXTURE::PLAY,
		[&]()->T_Screen{return SELECT_LEVEL; }));

	m_buttons.push_back(Btn(WIDTH_WINDOW / 17, HEIGHT_WINDOW / 10, Resources::TEXTURE::HELP,[]()->T_Screen {return MENU; }));
	m_buttons.push_back(Btn(WIDTH_WINDOW / 17, HEIGHT_WINDOW / 4, Resources::TEXTURE::SOUND, [&]()->T_Screen
		{ this->mute(m_buttons.capacity() - 1); return MENU; }));
}

void Menu::mute(int index) {

	if (m_lis.getGlobalVolume() > 0) {
		m_lis.setGlobalVolume(0);
		m_buttons[index].updateSprite(Resources::TEXTURE::MUTE);
	}
	else {
		m_lis.setGlobalVolume(50);
		m_buttons[index].updateSprite(Resources::TEXTURE::SOUND);

	}
}

void Menu::draw(sf::RenderWindow& target) const {
	Draw(target);
	target.draw(m_logo);
}
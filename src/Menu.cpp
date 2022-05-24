#include "Menu.h"

Menu::Menu(std::shared_ptr<Screen> ptr)
{
	//bg
	m_bg.setTexture(Resources::instance().getTexture(Resources::TEXTURE::BG));
	m_bg.setTextureRect(sf::IntRect(0, 0, WIDTH_WINDOW, HEIGHT_WINDOW));
	//left menu reac background
	m_menuBack = sf::RectangleShape({80,168});
	m_menuBack.setPosition(30, 30);
	m_menuBack.setFillColor(sf::Color(0xe2bb23a0));
	//logo
	m_logo.setTexture(Resources::instance().getTexture(Resources::TEXTURE::LOGO));
	m_logo.setOrigin(m_logo.getGlobalBounds().width / 2, m_logo.getGlobalBounds().height / 2);
	m_logo.setPosition(WIDTH_WINDOW / 2.f, HEIGHT_WINDOW / 2.5f);
	createBottons();
	m_screen = ptr;
}

void Menu::createBottons() {
	auto currentStart = sf::Vector2f(m_menuBack.getGlobalBounds().left + 40, m_menuBack.getGlobalBounds().top + 45);
	const auto middleSpace = sf::Vector2f(0, 84);

	auto nextStart = [&]()
	{
		currentStart += middleSpace;
		return currentStart;
	};

	m_buttons.push_back(Btn(WIDTH_WINDOW / 2.f, HEIGHT_WINDOW / 2.f + HEIGHT_WINDOW / 7.f, Resources::TEXTURE::PLAY,
		[&]() {m_screen->setScreen(T_Screen::Game); }));

	m_buttons.push_back(Btn(currentStart, Resources::TEXTURE::HELP, []() {}));
	m_buttons.push_back(Btn(nextStart(), Resources::TEXTURE::SOUND, [&]()
		{ this->mute(m_buttons.capacity()-1); }));
}


void Menu::handleMouse(sf::Event event, const sf::Vector2f cursorPos)
{
	for (auto& btn : m_buttons) {
		if (event.type == sf::Event::MouseMoved)
			btn.hover(cursorPos);
		else if (event.type == sf::Event::MouseButtonReleased)
			btn.Press(cursorPos);
	}
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


void Menu::Draw(sf::RenderWindow& target) const {
	target.draw(m_bg);
	target.draw(m_menuBack);
	target.draw(m_logo);
	for (auto& btn : m_buttons)
		btn.draw(target);
}
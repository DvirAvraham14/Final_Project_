#pragma once
#include "macro.h"
#include "Btn.h"
#include "Screen.h"
#include "Map.h"
#include <SFML\Audio.hpp>


class Menu
{
public:
	Menu() = default;
	Menu(std::shared_ptr<Screen>);
	void Draw(sf::RenderWindow& target) const;
	void handleMouse(sf::Event, const sf::Vector2f);
private:
	void createBottons();
	void mute(int index);

	sf::Sprite					m_bg;
	sf::RectangleShape			m_menuBack;
	sf::Sprite					m_logo;
	std::vector<Btn>			m_buttons;
	sf::Listener				m_lis;
	std::shared_ptr<Screen>		m_screen;
};
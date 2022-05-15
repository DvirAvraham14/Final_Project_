#pragma once
#include "macro.h"
#include "Btn.h"
#include <SFML\Audio.hpp>

class Menu
{
public:
	Menu();
	void Draw(sf::RenderWindow& target) const;
	void handleMouse(sf::Event, const sf::Vector2f);
private:
	void createBottons();
	void mute(int index);

	sf::Sprite			m_bg;
	sf::RectangleShape	m_menuBack;
	sf::Sprite			m_logo;
	std::vector<Btn>	m_buttons;
	sf::Listener		m_lis;
};
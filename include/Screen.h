#pragma once
#include "Btn.h"

class Screen {
public:
	Screen() = default;
	virtual ~Screen() = default;
	Screen(Resources::TEXTURE, T_Screen curr = MENU);
	virtual void draw(sf::RenderWindow& target) const = 0;
	virtual void handleScreen(sf::Event event, const sf::Vector2f cursorPos);
	virtual void update() {};
	void Draw(sf::RenderWindow& target) const;
protected:
	std::vector<Btn>	m_buttons;
	sf::RectangleShape  m_background;
	T_Screen            m_curr;
	
};
#pragma once
#include "GameData.h"
#include "Btn.h"

class Screen {
public:
	Screen() = default;
	Screen(Resources::TEXTURE, T_Screen curr = MENU);
	virtual ~Screen() = default;
	virtual void draw(sf::RenderWindow& target) const = 0;
	virtual void handleMouse(sf::Event event, const sf::Vector2f cursorPos);
	virtual void handleGame(sf::Time& delta) {}; 
	virtual void handleScreen() {};
	virtual void update() {};
	virtual void updateLevel() {};
	void Draw(sf::RenderWindow& target) const;
protected:
	std::vector<Btn>	m_buttons;
	sf::RectangleShape  m_background;
	T_Screen            m_curr;
private:

};
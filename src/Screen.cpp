#include"Screen.h"

//___________________________________________________

Screen::Screen(Resources::TEXTURE texture, T_Screen curr )
	:m_curr(curr)
{
	m_background.setSize({ WIDTH_WINDOW, HEIGHT_WINDOW });
	m_background.setTexture(&Resources::instance().getTexture(texture,true));		
	m_buttons.push_back(Btn(BACK_POS.x,BACK_POS.y, Resources::TEXTURE::BACK,
		[&]() ->T_Screen { return m_curr;}));
}

//___________________________________________________

void Screen::handleMouse(sf::Event event, const sf::Vector2f cursorPos)
{
	for (auto& btn : m_buttons) {
		if (event.type == sf::Event::MouseMoved)
			btn.hover(cursorPos);
		else if (event.type == sf::Event::MouseButtonReleased)
			btn.Press(cursorPos);
	}
}

//___________________________________________________

void Screen::Draw(sf::RenderWindow& target) const{
	target.draw(m_background);
	for (auto& i : m_buttons)
		i.draw(target);
}
#include "Btn.h"
#include "Resources.h"

//that class will show button or title on the board

Btn::Btn(float x, float y, Resources::TEXTURE sprite, std::function<void(void)> func)
	:m_position({ x, y }), m_func(func)
{
	m_sprite.setTexture(Resources::instance().getTexture(sprite));
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
	m_sprite.setPosition(m_position);
	m_sound.setBuffer(Resources::instance().getSound(Resources::SOUND::CLICK));
}

Btn::Btn(sf::Vector2f pos, Resources::TEXTURE sprite, std::function<void(void)> func)
	:Btn(pos.x, pos.y, sprite, func)
{
}

//__________________________________
void Btn::hover(const sf::Vector2f cursur) {
	if (m_func) {

		if (this->m_sprite.getGlobalBounds().contains(cursur))
			m_sprite.setColor(sf::Color(0xfafafacc));

		else
			m_sprite.setColor(sf::Color(0xfafafaff));
	}
}

//__________________________________
void Btn::Press(const sf::Vector2f cursur) {
	if (m_func && this->m_sprite.getGlobalBounds().contains(cursur)) {
		m_sound.play();
		m_func();
	}
}

//__________________________________
void Btn::updateSprite(Resources::TEXTURE sprite) {
	m_sprite.setTexture(Resources::instance().getTexture(sprite));
}


//__________________________________
void Btn::draw(sf::RenderWindow& window) const {
	window.draw(m_sprite);
}

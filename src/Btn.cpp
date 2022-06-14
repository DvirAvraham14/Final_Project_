#include "Btn.h"

Btn::Btn(float x, float y, Resources::TEXTURE sprite, std::function<T_Screen()> func)
	:m_position({ x, y }), m_func(func)
{
	m_sprite.setTexture(Resources::instance().getTexture(sprite));
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
	m_sprite.setPosition(m_position);
	m_sprite.setScale(WIDTH_WINDOW / 1100.0f, WIDTH_WINDOW / 1100.0f);
	m_sound.setBuffer(Resources::instance().getSound(Resources::SOUNDS::CLICK));
}

//__________________________________

Btn::Btn(sf::Vector2f pos, sf::Sprite sprite,  std::function<T_Screen()> func)
	:m_position(pos), m_func(func)
{
	m_sound.setBuffer(Resources::instance().getSound(Resources::SOUNDS::CLICK));
	m_sprite = sprite;
	m_sprite.setPosition(pos);
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
void Btn::Mark(const sf::Vector2f cursur) {
	if (m_func) {

		if (this->m_sprite.getGlobalBounds().contains(cursur))
			m_sprite.setColor(sf::Color(0x37373737));

		else
			m_sprite.setColor(sf::Color(0x00FF000F));
	}
}
//__________________________________
void Btn::Press(const sf::Vector2f cursur) {
	if (m_func && this->m_sprite.getGlobalBounds().contains(cursur)) {
	
		m_sound.play();
		GameData::instance().setScreen(m_func());
		if (GameData::instance().getScreen() == GAME) {
			m_sound.setBuffer(Resources::instance().getSound(Resources::SOUNDS::UNLOCK));
			m_sound.play();
		}

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

//__________________________________
void Btn::unlock(std::function<T_Screen()> func) {
	m_sprite.setTexture(Resources::instance().getTexture(Resources::TEXTURE::EMPTY_B));
	m_sprite.setColor(sf::Color{ 0x00FF000F });
	m_func = func;
 }

//__________________________________
bool Btn::isLock() const{
	if (m_sprite.getColor() == sf::Color{ 0x00FF000F })
		return false;
	return true;
}

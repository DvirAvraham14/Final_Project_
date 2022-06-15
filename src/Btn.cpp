#include "Btn.h"

//___________________________________________________

Btn::Btn(float x, float y, Resources::TEXTURE sprite, std::function<T_Screen()> func)
	:m_position({ x, y }), m_func(func)
{
	m_sprite.setTexture(Resources::instance().getTexture(sprite));
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / HALF, m_sprite.getGlobalBounds().height / HALF);
	m_sprite.setPosition(m_position);
	m_sprite.setScale(BTN_SCALE);
	m_sound.setBuffer(Resources::instance().getSound(Resources::SOUNDS::CLICK));
}

//___________________________________________________

Btn::Btn(sf::Vector2f pos, sf::Sprite sprite,  std::function<T_Screen()> func)
	:m_position(pos), m_func(func)
{
	m_sound.setBuffer(Resources::instance().getSound(Resources::SOUNDS::CLICK));
	m_sprite = sprite;
	m_sprite.setPosition(pos);
}

//___________________________________________________

void Btn::hover(const sf::Vector2f cursur) {
	if (m_func) {

		if (this->m_sprite.getGlobalBounds().contains(cursur))
			m_sprite.setColor(HOVERED);
		else
			m_sprite.setColor(ORIGINAL);
	}
}


//___________________________________________________

void Btn::Mark(const sf::Vector2f cursur) {
	if (m_func) {

		if (this->m_sprite.getGlobalBounds().contains(cursur))
			m_sprite.setColor(HOVERED_MAP);
		else
			m_sprite.setColor(ORIGINAL_MAP);
	}
}

//___________________________________________________

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

//___________________________________________________

void Btn::chooseLevel(const sf::Vector2f cursur) {
	if (m_levelFunc && this->m_sprite.getGlobalBounds().contains(cursur)) {
		m_sound.play();
		GameData::instance().setScreen(GAME);
		GameData::instance().setLevel(m_levelFunc());
	}
}

//___________________________________________________

void Btn::updateSprite(Resources::TEXTURE sprite) {
	m_sprite.setTexture(Resources::instance().getTexture(sprite));
}

//___________________________________________________

void Btn::draw(sf::RenderWindow& window) const {
	window.draw(m_sprite);
}

//__________________________________
void Btn::unlock(int index) {
	m_sprite.setTexture(Resources::instance().getTexture(Resources::TEXTURE::EMPTY_B));
	m_sprite.setColor(TRANSPARE);
	m_index = index;
	m_levelFunc = [&]() ->int { return m_index; };
	m_func = [&]() ->T_Screen { return GAME; };
 }

//__________________________________
void Btn::setPostion(sf::Vector2f pos) {
	m_sprite.setPosition(pos);
}

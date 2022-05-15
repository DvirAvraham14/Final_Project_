#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <functional>
#include <Resources.h>

//that class will show button or title on the board
class Btn {
private:
	sf::Sprite							m_sprite;
	sf::Vector2f						m_position;
	sf::Sound							m_sound;
	std::function<void(void)>		    m_func;
public:
	Btn() = default;
	Btn(float, float, Resources::TEXTURE sprite, std::function<void(void)> func=nullptr);
	Btn(sf::Vector2f, Resources::TEXTURE sprite, std::function<void(void)> func=nullptr);
	void hover(const sf::Vector2f cursur);
	void Press(const sf::Vector2f cursur);
	void updateSprite(Resources::TEXTURE);
	auto getPosition() const { return m_position; };
	void updatFunc(std::function<void(void)> func) { m_func = func; };

	void draw(sf::RenderWindow &window) const;
};
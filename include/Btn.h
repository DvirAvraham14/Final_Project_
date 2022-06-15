#pragma once
#include <functional>
#include "macro.h"
#include "GameData.h"

//that class will show button or title on the board
class Btn {
private:
	sf::Sprite							m_sprite;
	sf::Vector2f						m_position;
	sf::Sound							m_sound;
	std::function<T_Screen()>           m_func;
	std::function<int()>           m_levelFunc;
protected:
    int                                 m_index;
public:
	Btn() = default;
	Btn(float, float, Resources::TEXTURE sprite, std::function<T_Screen()> func=nullptr);
	Btn(sf::Vector2f pos, sf::Sprite sprite, std::function<T_Screen()> func = nullptr);
	void hover(const sf::Vector2f cursur);
	void Press(const sf::Vector2f cursur);
	void chooseLevel(const sf::Vector2f cursur);
	void Mark(const sf::Vector2f cursur);
	void updateSprite(Resources::TEXTURE);
	auto getPosition() const { return m_position; };
	void updatFunc(std::function<T_Screen()> func) { m_func = func; };
	void unlock(int index);
	void draw(sf::RenderWindow &window) const;
	bool isLock() const;
	void setPostion(sf::Vector2f pos);
};
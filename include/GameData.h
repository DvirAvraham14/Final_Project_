#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "Resources.h"
#include "macro.h"

class GameData {
public:
	static GameData& instance();
	sf::Text& getClockText()       { return m_clockText; }
	sf::Text& getCoinText()        { return m_coinText; }
	const int getLevel()           { return m_level; }
	const int getStars()           { return m_numOfStars; }
	const int getPlayer()          { return m_currPlayer; }
	Resources::TEXTURE getCurrBg() { return m_choosenBg; }
	T_Screen getScreen()           { return m_currScreen;}
	bool getIsNextLevel()          { return m_nextLevel; }

	void setClockText(sf::Text clockText)        { m_clockText = clockText; }
	void setCoinText(sf::Text coinText)          { m_coinText = coinText; }
	void setLevel(int level)                     { m_level = level; }
	void updateLevel(int val)                    { m_level += val; }
	void setStars(int stars)                     { m_numOfStars = stars; }
	void setPlayer(int currPlayer)               { m_currPlayer = currPlayer; }
	void chooseplayer(int index)                 { m_currPlayer += index; }
	void setCurrBg(Resources::TEXTURE choosenBg) { m_choosenBg = choosenBg; }
	void setScreen(T_Screen screen)              { m_currScreen = screen; }
	void setIsNextLevel(bool isNext)             { m_nextLevel = isNext; }

	void setClockString(std::string str, sf::Vector2f pos);
	void setCoinString(std::string str, sf::Vector2f pos);
private:

	sf::Text m_clockText = sf::Text();
	sf::Text m_coinText = sf::Text();
	int	m_level = 1;
	int m_numOfStars = 3;
	int m_currPlayer = Resources::Players::Spike;
	T_Screen m_currScreen = T_Screen::MENU;
	Resources::TEXTURE m_choosenBg = Resources::TEXTURE::CITY_NIGHT;
	bool m_nextLevel = true;
	
	GameData(){}
	GameData(const GameData&) = delete;
	void operator=(const GameData&) = delete;

};
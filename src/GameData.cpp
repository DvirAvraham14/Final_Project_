#include "GameData.h"

//___________________________________________________

GameData& GameData::instance()
{
	static GameData instance;
	return instance;
}

//___________________________________________________

void GameData::setCoinString(std::string str, sf::Vector2f pos)
{ 
	m_coinText.setString(str);  
	m_coinText.setPosition(pos); 
}

//___________________________________________________

void GameData::setClockString(std::string str, sf::Vector2f pos) 
{ 
	m_clockText.setString(str); 
	m_clockText.setPosition(pos); 
}
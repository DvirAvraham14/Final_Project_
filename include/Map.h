#pragma once

#include "macro.h"

class Map 
{
public:
	Map()=default;
	void createMap(int index);
	sf::ConvexShape getRoad() const{ return sf::ConvexShape(m_road); }
	std::vector<sf::Vector3f> getObstacels() const { return std::vector<sf::Vector3f>(m_obstacles); }
	std::vector<CoinData> getCoins() const { return std::vector<CoinData>(m_coins); }

private:
	std::vector<sf::Vector2f> readCord(std::string map);
	sf::ConvexShape			  m_road;
	std::vector<sf::Vector3f> m_obstacles;
	std::vector<CoinData>	  m_coins;
};
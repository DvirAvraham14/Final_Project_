#pragma once
#include "macro.h"
using std::vector;
const std::vector<sf::Vector2f>pitVec = { {0,0},{0,200},{220,200},{220,0} };

class Map 
{
public:
	Map()=default;
	void createMap(int index);
	sf::ConvexShape getRoad() { return sf::ConvexShape(m_road); }
	std::vector<sf::Vector3f> getObstacels() { return std::vector<sf::Vector3f>(m_obstacles); }
	std::vector<CoinData> getCoins() { return std::vector<CoinData>(m_coins); }
private:
	std::vector<sf::Vector2f> readCord(std::string map);
	sf::ConvexShape			  m_road;
	std::vector<sf::Vector3f> m_obstacles;
	std::vector<CoinData>	 m_coins;
};
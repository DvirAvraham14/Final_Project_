#pragma once
#include "macro.h"
using std::vector;

class Map 
{
public:
	Map()=default;
	void createMap(int index);
	sf::ConvexShape getRoad() { return sf::ConvexShape(m_road); }
	std::vector<sf::Vector3f> getObstacels() { return std::vector<sf::Vector3f>(m_obstacles); }
private:
	std::vector<sf::Vector2f> readCord(std::string map);
	sf::ConvexShape			m_road;
	std::vector<sf::Vector3f> m_obstacles;
};
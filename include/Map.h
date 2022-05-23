#pragma once
#include "macro.h"

using std::vector;

class Map
{
public:
	Map();
	void draw(sf::RenderWindow& target) const;
	void setView(sf::View &view);
private:
	vector<sf::Vector2f> readCord(std::string map);
	void openAndInsertData(std::string map);
	float calculateRectSize(int x1,int y1,int x2,int y2);

	std::string				m_textMapsPath[NUM_OF_MAPS] = {
							"map1.txt"
	};

	void addMaps();
	int m_mapNumber = 0;
	std::vector<sf::Sprite>m_mapSprite;
	std::vector<sf::ConvexShape>m_mapRoad;
	sf::ConvexShape m_road;
};
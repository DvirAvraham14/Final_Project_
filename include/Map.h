#pragma once
#include "macro.h"

using std::vector;

class Map
{
public:
	Map(std::shared_ptr<b2World>);
	void addMaps(int index);
	void draw(sf::RenderWindow& target) const;
	sf::ConvexShape& getRoad() { return m_road; }
	//void setView(sf::View &view);
private:
	vector<sf::Vector2f> readCord(std::string map);
	void openAndInsertData(std::string map);
	void CreateGround();
	std::string				m_textMapsPath[NUM_OF_MAPS] = {
							"map1.txt"
	};
	

//	int m_mapNumber = 0;
	std::vector<sf::Sprite>m_mapSprite;
//	std::vector<sf::ConvexShape>m_mapRoad;
	sf::ConvexShape m_road;
	std::shared_ptr<b2World> m_world;
	b2Body* m_body;
};
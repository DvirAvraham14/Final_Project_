#pragma once
#include "GameObject.h"
using std::vector;

class Map : public GameObject
{
public:
	//Map(std::shared_ptr<b2World> );
	using GameObject::GameObject;
	void addMaps(int index);
	void draw(sf::RenderWindow& target);
	sf::ConvexShape& getRoad() { return m_road; }

private:
	vector<sf::Vector2f> readCord(std::string map);
	void openAndInsertData(std::string map);
	void CreateGround();
	std::string				m_textMapsPath[NUM_OF_MAPS] = {
							"map1.txt"
	};

	std::vector<sf::Sprite> m_mapSprite;
	sf::ConvexShape m_road;
	//std::shared_ptr<b2World> m_world;
	//b2Body* m_body;
};
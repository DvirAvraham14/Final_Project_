#include "Map.h"

//Map::Map(std::shared_ptr<b2World> world)
//{
//	m_world = world;
//}


void Map::addMaps(int index) {
	openAndInsertData(m_textMapsPath[index-1]);
	auto mapIndex=static_cast<Resources::TEXTURE>(index+6);
	sf::Sprite bg;
	bg.setTexture(Resources::instance().getTexture(mapIndex, true));
	bg.setTextureRect({0,0,10000, HEIGHT_WINDOW});
	m_mapSprite.push_back(bg);
}


void Map::openAndInsertData(std::string map) {

	vector<sf::Vector2f> points = readCord(map);

	m_road.setPointCount(points.size() + 2);
	for (auto i = 0; i < points.size(); i++)
		m_road.setPoint(i, sf::Vector2f(points[i].x, points[i].y));
	m_road.setPoint(points.size(), sf::Vector2f(points[points.size() - 1].x, WIDTH_WINDOW));
	m_road.setPoint(points.size() + 1, sf::Vector2f(points.begin()->x, WIDTH_WINDOW));
	m_road.setFillColor(sf::Color::Black);

	CreateGround();
}


vector<sf::Vector2f> Map::readCord(std::string map) {
	std::ifstream file;
	std::string line;
	std::vector<sf::Vector2f> points;
	file.open(map);
	
	while (std::getline(file, line)) {

		std::istringstream iss(line);
		float x, y;
		iss >> x >> y;
		points.push_back(sf::Vector2f(x, y));
	}
	return points;
}


void Map::CreateGround() {
	// The body is also added to the world
	b2BodyDef groundBodyDef;
	groundBodyDef.type = b2_staticBody;
	m_body = m_world->CreateBody(&groundBodyDef);

	// Define the ground box shape
	//b2ChainShape groundBox;
	auto size = m_road.getPointCount() - 2;
	b2Vec2* vs = new b2Vec2[size];
	for (auto i = 0; i < size; i++)
		vs[i].Set(m_road.getPoint(i).x / SCALAR, m_road.getPoint(i).y / SCALAR);
	b2ChainShape chain;
	chain.CreateLoop(vs, size);
	m_body->CreateFixture(&chain, 1.0f);
	m_body->SetUserData(this);
}

void Map::draw(sf::RenderWindow& target)  {
	target.draw(m_mapSprite[0]);
	target.draw(m_road);
}



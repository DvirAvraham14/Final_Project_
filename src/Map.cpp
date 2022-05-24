#include "Map.h"

Map::Map(std::shared_ptr<b2World> world)
:m_world(world) {
	addMaps();
}


void Map::addMaps() {
	for (auto& map : m_textMapsPath) {
		openAndInsertData(map);
	}
	sf::Sprite bg;
	bg.setTexture(Resources::instance().getTexture(Resources::TEXTURE::MAP1, true));
	bg.setTextureRect({0,0,10000, HEIGHT_WINDOW});
	m_mapSprite.push_back(bg);
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

void Map::CreateGround() {
	// The body is also added to the world
	b2BodyDef groundBodyDef;
	b2Body* groundBody = m_world->CreateBody(&groundBodyDef);

	// Define the ground box shape
	//b2ChainShape groundBox;
	auto size = m_road.getPointCount() - 2;
	b2Vec2* vs = new b2Vec2[size];
	for (auto i = 0; i < size; i++)
		vs[i].Set(m_road.getPoint(i).x / SCALAR, m_road.getPoint(i).y / SCALAR);
	b2ChainShape chain;
	chain.CreateLoop(vs, size);
	groundBody->CreateFixture(&chain, 0.0f);
}

void Map::draw(sf::RenderWindow& target) const {
	target.draw(m_mapSprite[0]);
	target.draw(m_road);
}



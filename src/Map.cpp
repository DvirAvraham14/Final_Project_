#include "Map.h"

Map::Map() {
	addMaps();
}


void Map::addMaps() {
	for (auto& map : m_textMapsPath) {
		openAndInsertData(map);
	}
	sf::Sprite bg;
	bg.setTexture(Resources::instance().getSprite(Resources::TEXTURE::MAP1, true));
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
}



float Map::calculateRectSize(int x1, int y1, int x2, int y2) {
	float dis = pow(x2 - x1, 2) + pow(y2 - y1, 2);
	dis = pow(dis, 0.5);
	return dis;
}


void Map::setView(sf::View &view) {
	sf::FloatRect fBounds(0.f, 0.f, 1000.f, 1000.f);
	sf::IntRect   iBounds(fBounds);
	sf::Sprite    Sprite(Resources::instance().getSprite(Resources::TEXTURE::MAP1, true), iBounds);
	Sprite.setPosition(fBounds.left, fBounds.top - 1000.f + view.getSize().y);

	m_mapSprite[0] = Sprite;
}



void Map::draw(sf::RenderWindow& target) const {
	target.draw(m_mapSprite[m_mapNumber]);
	target.draw(m_road);
}



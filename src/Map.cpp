#include "Map.h"
Map::Map() {
	addMaps();
}
void Map::addMaps() {
	for (auto& map : m_textMapsPath) {
		openAndInsertData(map);
	}
	sf::Sprite bg;
	bg.setTexture(Resources::instance().getSprite(Resources::TEXTURE::MAP1));
	m_mapSprite.push_back(bg);
}
void Map::openAndInsertData(std::string map) {
	std::ifstream file;
	file.open(map);
	std::string line;
	std::vector<sf::Vector2f> points;
	while (std::getline(file, line)) {

		std::istringstream iss(line);
		float x, y;
		iss >> x >> y;
		points.push_back(sf::Vector2f(x, y));
	}
	sf::ConvexShape shape;
	shape.setPointCount(points.size() + 2);
	for (auto i = 0; i < points.size(); i++)
		shape.setPoint(i, sf::Vector2f(points[i].x, points[i].y));

	shape.setPoint(points.size(), sf::Vector2f(points[points.size() - 1].x, WIDTH_WINDOW));
	shape.setPoint(points.size() + 1, sf::Vector2f(points.begin()->x, WIDTH_WINDOW));
	shape.setFillColor(sf::Color::Black);
	m_road = shape;
}
float Map::calculateRectSize(int x1, int y1, int x2, int y2) {
	float dis = pow(x2 - x1, 2) + pow(y2 - y1, 2);
	dis = pow(dis, 0.5);
	return dis;
}
void Map::setView(sf::View &view) {
	sf::FloatRect  fBounds(0.f, 0.f, 1000.f, 1000.f);
	sf::IntRect    iBounds(fBounds);
	sf::Sprite                      Sprite(Resources::instance().getSprite(Resources::TEXTURE::MAP1), iBounds);
	Sprite.setPosition(fBounds.left, fBounds.top - 1000.f + view.getSize().y);

	m_mapSprite[0] = Sprite;
}
void Map::draw(sf::RenderWindow& target) const {
	target.draw(m_mapSprite[m_mapNumber]);
	target.draw(m_road);
}



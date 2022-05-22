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

		// Read from the file contents
		//float x1, y1,x2,y2;
		//iss >> x1>> y1>> x2>> y2;
		float x, y;
		iss >> x >> y;
		points.push_back(sf::Vector2f(x, y));
		//sf::ConvexShape shape;
		//shape.setPointCount(4);
		//shape.setPoint(0, sf::Vector2f(x1, y1));
		//shape.setPoint(1, sf::Vector2f(x2, y2));
		//shape.setPoint(2, sf::Vector2f(x2, WIDTH_WINDOW));
		//shape.setPoint(3, sf::Vector2f(x1, WIDTH_WINDOW));
		//shape.setFillColor(sf::Color::Black);

		//m_mapRoad.push_back(shape);
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
void Map::draw(sf::RenderWindow& target) const {
	target.draw(m_mapSprite[m_mapNumber]);
	target.draw(m_road);
	//for (auto& line : m_mapRoad) {
	//	target.draw(line);
	//}
	//sf::RectangleShape rect(sf::Vector2f(5, 5));

}


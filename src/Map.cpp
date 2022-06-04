#include "Map.h"


void Map::createMap(int index) {
	m_obstacles.clear();
	std::string path = "map" + std::to_string(index) + ".txt";
	vector<sf::Vector2f> points;
	points = readCord(path);
	m_road.setPointCount(points.size() + 2);

	for (auto i = 0; i < points.size(); i++)
		m_road.setPoint(i, sf::Vector2f(points[i].x, points[i].y));
	m_road.setPoint(points.size(), sf::Vector2f(points[points.size() - 1].x, INT32_MAX));
	m_road.setPoint(points.size() + 1, sf::Vector2f(0, INT32_MAX));
	m_road.setFillColor(sf::Color::Black);
}


vector<sf::Vector2f> Map::readCord(std::string map) {
	std::ifstream file;
	std::string line;
	std::vector<sf::Vector2f> points;
	file.open(map);
	while (std::getline(file, line)) {
		float x, y,d;	
		if (line.find(map::DOT) != std::string::npos) {
			line.erase(line.begin(), line.begin()+2);

			std::istringstream iss(line);
			iss >> x >> y;
			points.push_back(sf::Vector2f(x, y));
		}
		else if (line.find(map::OBSTACLE) != std::string::npos) {
			line.erase(line.begin(), line.begin() + 2);

			std::istringstream iss(line);
			float x, y ,z;
			iss >> x >> y >>z;
			std::vector<sf::Vector2f>vec = { {0,0},{0,200},{200,200},{200,0} };
			if (x == 2) {
				for (auto i = 0; i < 4; i++)
					points.push_back(sf::Vector2f(y, z) + vec[i]);
				z += 200;
				y += 100;
			}
			
			m_obstacles.push_back(sf::Vector3f(x,y,z));
		}
	}

	return points;
}

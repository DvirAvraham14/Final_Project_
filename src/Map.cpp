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
	m_road.setOutlineThickness(WIDTH_WINDOW/-33.3f);
	m_road.setOutlineColor(sf::Color(0x373737FF));
	m_road.setFillColor(sf::Color(0x555555FF));
}


vector<sf::Vector2f> Map::readCord(std::string map) {

	std::ifstream file;
	std::string line;
	std::vector<sf::Vector2f> points;
	file.open(map);
	while (std::getline(file, line)) {
		float x, y, d;
		if (line.find(map::DOT) != std::string::npos) {
			line.erase(line.begin(), line.begin() + 2);

			std::istringstream iss(line);
			iss >> x >> y;
			points.push_back(sf::Vector2f(x, y));
		}
		else if (line.find(map::OBSTACLE) != std::string::npos) {
			line.erase(line.begin(), line.begin() + 2);

			std::istringstream iss(line);
			float x, y, z;
			iss >> x >> y >> z;
			if (x == 2) {
				for (auto i = 0; i < PIT_VEC.size(); i++)
					points.push_back(sf::Vector2f(y, z) + PIT_VEC[i]);
				z += PIT_SIZE;
				y += PIT_SIZE/2;
			}

			m_obstacles.push_back(sf::Vector3f(x, y, z));
		}
		else if (line.find(map::COINS) != std::string::npos) {
			line.erase(line.begin(), line.begin() + 2);
			std::istringstream iss(line);
			bool line;
			float x, y, z;
			iss >> x >> y >> z>>line;
			m_coins.push_back({ sf::Vector3f(x, y, z) ,line});
		}
	}
	return points;
}

#include "Map.h"

//___________________________________________________

void Map::createMap(int index) {
	sf::ConvexShape road;
	m_coins.clear();
	m_obstacles.clear();
	std::string path = "map" + std::to_string(index) + ".txt";
	std::vector<sf::Vector2f> points;
	points = readCord(path);
	road.setPointCount(points.size() + CONST_POINT);

	for (auto i = 0; i < points.size(); i++)
		road.setPoint(i, sf::Vector2f(points[i].x, points[i].y));
	road.setPoint(points.size(), sf::Vector2f(points[points.size() - 1].x, INT32_MAX));
	road.setPoint(points.size() + 1, sf::Vector2f(0, INT32_MAX));
	road.setOutlineThickness(ROAD_THICKNESS);
	road.setOutlineColor(ROAD_OUTLINE_COLOR);
	road.setFillColor(ROAD_COLOR);
	m_road = road;
}

//___________________________________________________

std::vector<sf::Vector2f> Map::readCord(std::string map) {
	std::ifstream file;
	std::string line;
	std::vector<sf::Vector2f> points;
	file.open(map);
	while (std::getline(file, line)) {
		float x, y, d;
		if (line.find(map::DOT) != std::string::npos) {
			line.erase(line.begin(), line.begin() + CONST_POINT);

			std::istringstream iss(line);
			iss >> x >> y;
			points.push_back(sf::Vector2f(x, y));
		}
		else if (line.find(map::OBSTACLE) != std::string::npos) {
			line.erase(line.begin(), line.begin() + CONST_POINT);

			std::istringstream iss(line);
			float x, y, z;
			iss >> x >> y >> z;
			if (x == 2) {
				for (auto i = 0; i < PIT_VEC.size(); i++)
					points.push_back(sf::Vector2f(y, z) + PIT_VEC[i]);
				z += PIT_SIZE;
				y += PIT_SIZE / HALF;
			}

			m_obstacles.push_back(sf::Vector3f(x, y, z));
		}
		else if (line.find(map::COINS) != std::string::npos) {
			line.erase(line.begin(), line.begin() + CONST_POINT);
			std::istringstream iss(line);
			bool line;
			float x, y, z;
			iss >> x >> y >> z >> line;
			m_coins.push_back({ sf::Vector3f(x, y, z) ,line });
		}
	}
	return points;
}

#include"MangeLevel.h"
void ManageLevel::manageAction(std::vector<std::shared_ptr<MovingObject>> vehicles, sf::Clock& clock){
	for (auto& vehicle : vehicles) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			vehicle->drive();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			vehicle->jump();
	}
	
}
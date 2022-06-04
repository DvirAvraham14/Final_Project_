#include"MangeLevel.h"
void ManageLevel::manageAction(std::vector<std::shared_ptr<MovingObject>> vehicles, sf::Event event){
	for (auto& vehicle : vehicles) {
		//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		//	vehicle->jump();
		//	vehicle->drive();
		//}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			vehicle->jump();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			vehicle->drive(40);
	}
}


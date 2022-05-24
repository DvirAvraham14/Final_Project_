#pragma once
#include"MovingObject.h"
class ManageLevel
{
public:
	ManageLevel()=default;
	void manageAction(std::vector<std::shared_ptr<MovingObject>> vehicles,sf::Clock &clock);
private:

};
#include <iostream>
#include "Controller.h"

int main() try
{
	Controller game;
	game.run();

	return EXIT_SUCCESS;
}
catch (std::exception& e) {
	std::cout << e.what();
}

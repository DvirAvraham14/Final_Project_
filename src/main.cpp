#include <iostream>
#include "Controller.h"

int main() 
{
	try {
		Controller game;
		game.run();
	}
	catch (std::exception& e) {
		std::cout << e.what();
	}
	return EXIT_SUCCESS;
}


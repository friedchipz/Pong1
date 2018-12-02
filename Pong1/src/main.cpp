#include <iostream>
#include "game.h"
int main(int argc, char * argv[]) {
	try {
		Game * game = new Game();
		game->gameLoop();
		delete game;
	}
	catch (const std::exception & e) {
		std::cout << e.what() << std::endl;
	}
	return 0;
}
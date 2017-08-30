#include <iostream>
#include "Game.h"

int main(int argc, char** argv) {
	Game *g = new Game;
	g->runGame(argc, argv);
	return 0;
}
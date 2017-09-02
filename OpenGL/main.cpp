#include <iostream>
#include <GL/glut.h>
#include "Game.h"

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	Game *g = new Game;
	g->runGame();
	return 0;
}
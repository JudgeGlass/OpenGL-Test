#include "TextOverlay.h"


#include <GL/glut.h>
//#include <GLUT/glut.h>
#include <thread>
#include <iostream>
#include <string>
#include <sstream>

TextOverlay::TextOverlay(std::string text, int x, int y) {
	char menu[80];
	std::stringstream ss;
	ss << text;
	std::string text1 = ss.str();
	const char *finalText = text1.c_str();
	strcpy_s(menu, finalText);
	int len;
	len = strlen(menu);

	glColor3f(1, 1, 1);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	gluOrtho2D(0, 600, 0, 600);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glLoadIdentity();

	glRasterPos2i(x, y);


	for (int i = 0; i < len; ++i)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, menu[i]);
	}

	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}
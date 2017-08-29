
#include <GL/glut.h>
//#include <GLUT/glut.h>
#include <thread>
#include <iostream>
#include <string>
#include <sstream>

#include "TextOverlay.h"

long cool = 0;
std::string FPS = "";
std::string TestThread() {
	return FPS;
}


void init2D(float r, float g, float b)
{
	glClearColor(r, g, b, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-50.0, 50.0, -50.0, 50.0);
}

void rectangle()
{
	glBegin(GL_QUADS);
	glColor3f(1.0,0.0,0.0);
	glVertex3f(-1.0f*30, -1.0f * 30, 0.0f);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(1.0f * 30, -1.0f * 30, 0.0f);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(1.0f * 30, 1.0f * 30, 0.0f);
	glColor3f(1.0, 1.0, 0.0);
	glVertex3f(-1.0f * 30, 1.0f * 30, 0.0f);
	glEnd();
}

void debugText()
{
	char menu[80];
	std::stringstream ss;
	ss << "FPS: "+FPS;
	std::string wow = ss.str();
	const char *test = wow.c_str();
	strcpy_s(menu,test);
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

	glRasterPos2i(0, 565);


	for (int i = 0; i < len; ++i)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, menu[i]);
	}

	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void versionInfo()
{
	char menu[80];
	strcpy_s(menu, "OpenGL test by: Hunter Wilcox");
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

	glRasterPos2i(0, 583);


	for (int i = 0; i < len; ++i)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, menu[i]);
	}

	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}
int frame = 0;
int currenttime;
int timebase = 0;
double delta = 0;
void display()
{
	
	if (delta > 360)
		delta = 0;
	else if (delta > 180)
		delta -= .00001;
	else
		delta += .00001;

	frame++;

	//get the current time
	currenttime = glutGet(GLUT_ELAPSED_TIME);

	//check if a second has passed
	if (currenttime - timebase > 1000)
	{
		std::stringstream ss;
		ss << (int)(frame*1000.0 / (currenttime - timebase));
		FPS = ss.str();
		std::cout << "FPS: " << ss.str() << std::endl;
		//glutSetWindowTitle(ss.str());
		timebase = currenttime;
		frame = 0;
	}

	

	glClear(GL_COLOR_BUFFER_BIT);



	//glPushMatrix();
	//glTranslatef(0.0, 0.0, -45.0);
	glRotatef(delta, 0.0, 0.0, 1.0);
	rectangle();
	//glPopMatrix();
	
	TextOverlay *t = new TextOverlay("Text class test", 0, 120);
	
	versionInfo();
	debugText();
	

	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowPosition(0, 0);
	glutInitWindowSize(800, 600);
	glutCreateWindow("OpenGL test Alpha");
	init2D(0.0f, 0.0f, 0.0f);
	glutDisplayFunc(display);
	
	std::thread update(TestThread);
	glutDisplayFunc(display);
	glutIdleFunc(display);
	
	glutMainLoop();
	
}

#include <GL/glut.h>
//#include <GLUT/glut.h>
#include <thread>
#include <iostream>
#include <string>
#include <sstream>
#include "Logger.h"

#include "TextOverlay.h"

long cool = 0;
std::string FPS = "";

double rotate_y;
double rotate_x;

struct GlFPS {
	int frame = 0;
	int currenttime;
	int timebase = 0;
};

enum CubeFaces {
	Front,
	Back,
	Left,
	Right,
	Top,
	Bottom
};

std::string TestThread() {
	return FPS;
}

void init2D(float r, float g, float b)
{
	std::cout << CubeFaces::Front << std::endl;
	std::cout << CubeFaces::Back << std::endl;
	glClearColor(r, g, b, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-50.0, 50.0, -50.0, 50.0);
	glScalef(15.0, 15.0, 0.0);
}

void rectangle()
{
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 1.0);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glEnd();

	// Purple side - RIGHT
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 0.0);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glEnd();

	// Green side - LEFT
	glBegin(GL_POLYGON);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glEnd();

	// Blue side - TOP
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glEnd();

	// Red side - BOTTOM
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, -0.5, -0.5);
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

void specialKeys(int key, int x, int y) {

	//  Right arrow - increase rotation by 5 degree
	if (key == GLUT_KEY_RIGHT)
		rotate_y += 5;

	//  Left arrow - decrease rotation by 5 degree
	else if (key == GLUT_KEY_LEFT)
		rotate_y -= 5;

	else if (key == GLUT_KEY_UP)
		rotate_x += 5;

	else if (key == GLUT_KEY_DOWN)
		rotate_x -= 5;

	//  Request display update
	glutPostRedisplay();

}

double delta = 0;
GlFPS glFps;
void display()
{
	
	if (delta > 360)
		delta = 0;
	else if (delta > 180)
		delta -= .00001;
	else
		delta += .00001;
	
	glFps.frame++;

	//get the current time
	glFps.currenttime = glutGet(GLUT_ELAPSED_TIME);

	//check if a second has passed
	if (glFps.currenttime - glFps.timebase > 1000)
	{
		std::stringstream ss;
		ss << static_cast<int> (glFps.frame*1000.0 / (glFps.currenttime - glFps.timebase));
		FPS = ss.str();
		std::cout << "FPS: " << ss.str() << std::endl;
		//glutSetWindowTitle(ss.str());
		glFps.timebase = glFps.currenttime;
		glFps.frame = 0;
	}

	

	glClear(GL_COLOR_BUFFER_BIT);



	//glPushMatrix();
	//glTranslatef(0.0, 0.0, -45.0);
	
	//glRotatef(delta, 0.0, 1.0, 0.0);
	glRotatef((GLfloat)rotate_x/100, (GLfloat) 1.0, (GLfloat)0.0, (GLfloat)0.0);
	glRotatef((GLfloat)rotate_y/100, (GLfloat)0.0, (GLfloat)1.0, (GLfloat)0.0);
	rectangle();
	//glPopMatrix();
	
	TextOverlay *t = new TextOverlay("Text class test", 0, 120, 0,1.0,7.0);
	
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
	glutSpecialFunc(specialKeys);
	glutMainLoop();
}

/*
 * This file includes anything and everything to do with processing events.
 * 
 * 
 * 
 * 
 */

#include "config.h"
#include <GL/glut.h>


void reshape(int w, int h) 
{
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(FOV, (GLfloat) w/ (GLfloat) h, 40, 5000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	
	
}

void mouse(int button, int state, int x, int y) 
{
	
	
	
}


void keyboard(unsigned char key, int x, int y)
{
	
	
	
	
}



void specialKeyboard(int key, int x, int y)
{
	
	
}




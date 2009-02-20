
/*
 * This file includes anything and everything to do with processing events.
 *
 *
 *
 *
 */

#include "config.h"
#include <GL/glut.h>
#include <stdio.h>
#include "display.h"
#include "Cursor/WiiCursor.h"

void reshape(int w, int h)
{

    GetDisplayed()->Reshape(w, h);
	/*
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(FOV, (GLfloat) w/ (GLfloat) h, 40, 5000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	*/


}

void mouse(int button, int state, int x, int y)
{

    int width = glutGet(GLUT_WINDOW_WIDTH);
    int height = glutGet(GLUT_WINDOW_HEIGHT);

    //printf("Width = %i, H = %i\n", width, height);

    int cursorX = ((float)x/(float)width)*1024.0;
    int cursorY = ((float)y/(float)height)*768.0;

    //printf("Inside mouse: (%i, %i)\n", cursorX, cursorY);
	_cursor->ProcessCoordinates(cursorX, cursorY, cursorX, cursorY);

	int points[2];
	_cursor->GetCurrentCursor(points);

	GetDisplayed()->Select(points[0], points[1]);

}


void keyboard(unsigned char key, int x, int y)
{




}



void specialKeyboard(int key, int x, int y)
{


}




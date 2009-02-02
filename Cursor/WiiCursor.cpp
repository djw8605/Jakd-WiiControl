#include "WiiCursor.h"
#include <GL/glut.h>


WiiCursor::WiiCursor()
{
}

WiiCursor::~WiiCursor()
{
}


WiiCursor* WiiCursor::GetInstance()
{
    
    static WiiCursor* cursor = new WiiCursor();
    return cursor;
    
    
}


void WiiCursor::Render()
{

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    
    gluOrtho2D(0, 1024, 0, 768);

    glMatrixMode(GL_MODELVIEW);
    
    glPushMatrix();
    
    glBegin(GL_QUADS);
    
    glVertex2f(cursorX-10, cursorY-10);
    glVertex2f(cursorX-10, cursorY+10);
    glVertex2f(cursorX+10, cursorY+10);
    glVertex2f(cursorX+10, cursorY-10);

    glEnd();
    
    glPopMatrix();
    
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

}


void WiiCursor::ProcessCoordinates(short x1, short y1, short x2, short y2)
{
    
    /* Do a bunch of calculations to find the on screen coordinates */
    cursorX = (x1+x2)/2;
    cursorY = 768-(y1+y2)/2;
    
    
    
    
}






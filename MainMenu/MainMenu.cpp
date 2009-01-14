#include "MainMenu.h"
#include <GL/glut.h>
#include <stdio.h>

MainMenu::MainMenu()
{
}

MainMenu::~MainMenu()
{
}


void MainMenu::Init()
{
    
    int width = glutGet(GLUT_WINDOW_WIDTH);
    int height = glutGet(GLUT_WINDOW_WIDTH);
        
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glViewport(0, 0, (GLsizei) width, (GLsizei) height);
    gluOrtho2D(0, 1000, 0, 1000);
    
    glMatrixMode(GL_MODELVIEW);
    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
}

void MainMenu::DeInit()
{
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    
}


void MainMenu::Render()
{
    
    glPushMatrix();
    

    glTranslatef(0, 0, 0);
    glColor4f(0.0, 0.0, 1.0, 0.5);
    glBegin(GL_QUADS);

    glVertex2f(100, 100);
    glVertex2f(900, 100);
    glVertex2f(900, 900);
    glVertex2f(100, 900);
    glEnd();
    
    
    
    
    glPopMatrix();
}

void MainMenu::Select(int x, int y)
{
    
    
    
}

void MainMenu::Reshape(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    gluOrtho2D(0, 1000, 0, 1000);
    
    glMatrixMode(GL_MODELVIEW);
    
}




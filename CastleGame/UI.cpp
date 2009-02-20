#include "UI.h"
#include <GL/glut.h>
#include "CastleGame/PlayerStats.h"
#include <stdio.h>
#include <math.h>


#define PERCENT_HEALTH 0.97

UI::UI()
{
}

UI::~UI()
{
}

UI* UI::GetInstance()
{
    static UI* instance = new UI();
    return instance;
    
}

void UI::Render()
{
    /* Set up the 2D display */
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glViewport(0, 0, (GLsizei) glutGet(GLUT_WINDOW_WIDTH), (GLsizei) glutGet(GLUT_WINDOW_HEIGHT));
    gluOrtho2D(0, 1000.0, 0, 1000.0);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glDisable(GL_FOG);
    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glBlendFunc(GL_SRC_ALPHA,GL_ONE);
    
    this->RenderHealthBar();
    
    this->RenderWallHealth();
    
    glEnable(GL_LIGHTING);
    glEnable(GL_FOG);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    
    
    
}

void UI::RenderHealthBar()
{
    
    glPushMatrix();
        glLoadIdentity();
        /* Position Health Bar */
        glTranslatef(50.0, 940.0, 0.0);
        glScalef(4.0, 2.0, 1.0);
        
        this->DrawBar(_player->GetPlayerPerc());
        
        glPopMatrix();
    
}


void UI::RenderWallHealth()
{
    glPushMatrix();
    glLoadIdentity();
    /* Position Health Bar */
    glTranslatef(550.0, 940.0, 0.0);
    glScalef(4.0, 2.0, 1.0);
    
    this->DrawBar(_player->GetWallPerc());
    
    glPopMatrix();
    
}

void UI::DrawBar(float healthPerc)
{
    
    
    static float boxDim[] = { 100.0, 30.0 };
    static float innerDim[] = {  (boxDim[0] - boxDim[0]*PERCENT_HEALTH)/2, /* Bottom left translate */
                                                            (boxDim[0] - boxDim[0]*PERCENT_HEALTH)/2, /* Bottom bottom translate */
                                                            boxDim[0] - (boxDim[0] - boxDim[0]*PERCENT_HEALTH),
                                                            boxDim[1] - (boxDim[0] - boxDim[0]*PERCENT_HEALTH) };
    
    //printf("%lf, %lf, %lf, %lf \n", innerDim[0], innerDim[1], innerDim[2], innerDim[3]);
    

   
    
    
    /* Outline of box */
    glColor4f(1.0, 1.0, 1.0, 1.0);
    glBegin(GL_LINE_LOOP);
    glVertex3f(0.0, 0.0, 0.1);
    glVertex3f(0.0, boxDim[1], 0.1);
    glVertex3f(boxDim[0], boxDim[1], 0.1);
    glVertex3f(boxDim[0], 0.0, 0.1);
    glEnd();
    
    /* Draw transparent inside of box */
    glColor4f(1.0, 1.0, 1.0, 0.5);
    glBegin(GL_QUADS);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, boxDim[1], 0.0);
    glVertex3f(boxDim[0], boxDim[1], 0.0);
    glVertex3f(boxDim[0], 0.0, 0.0);
    glEnd();
    
    
    /* Draw actual Health */
    
    glColor4f(1.0-healthPerc, healthPerc, 0.0, 1.0);
    glTranslatef(innerDim[0], innerDim[1], 0.0);
    glScalef(healthPerc, 1.0, 1.0);
    glBegin(GL_QUADS);
    glVertex3f(0.0, 0.0, 0.1);
    glVertex3f(innerDim[2], 0.0, 0.1);
    glVertex3f(innerDim[2], innerDim[3], 0.1);
    glVertex3f(0.0, innerDim[3], 0.1);
    glEnd();
    
 
    
}




#include "UI.h"
#include <GL/glut.h>
#include "CastleGame/PlayerStats.h"
#include <stdio.h>
#include <math.h>
#include "TextPrinter/BitMapText.h"
#include "display.h"


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

    //glBlendFunc(GL_SRC_ALPHA,GL_ONE);

    this->RenderHealthBar();

    this->RenderWallHealth();
    
    this->RenderLevelInfo();
    
    this->RenderKilledInfo();

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

        this->DrawBar(_player->GetPlayerPerc(), (char*)"Player");

        glPopMatrix();

}



void UI::RenderWallHealth()
{
    glPushMatrix();
    glLoadIdentity();
    /* Position Health Bar */
    glTranslatef(550.0, 940.0, 0.0);
    glScalef(4.0, 2.0, 1.0);

    this->DrawBar(_player->GetWallPerc(), (char*)"Wall");

    glPopMatrix();

}



void UI::DrawBar(float healthPerc, char* inside)
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
    glTranslatef(innerDim[0], innerDim[1], 0.0);
    glColor4f(1.0-healthPerc, healthPerc, 0.0, 0.75);

    glPushMatrix();
    glScalef(healthPerc, 1.0, 1.0);
    glBegin(GL_QUADS);
    glVertex3f(0.0, 0.0, 0.1);
    glVertex3f(innerDim[2], 0.0, 0.1);
    glVertex3f(innerDim[2], innerDim[3], 0.1);
    glVertex3f(0.0, innerDim[3], 0.1);
    glEnd();
    glPopMatrix();
    
    glPushMatrix();
    glColor4f(1.0, 1.0, 1.0, 1.0);
    glTranslatef(0.0, 0.0, 0.5);
    freetype::print(*(GetFont()), 10, 10, inside);
    glPopMatrix();

}


void UI::RenderLevelInfo()
{
    
    glPushMatrix();
    glTranslatef(460, 970, 0.0);
    freetype::print(*(GetFont()), 10, 10, (char*) "Level");
    glTranslatef(7, -60, 0.0);
    glScalef(3.0, 3.0, 1.0);
    
    freetype::print(*(GetFont()), 10, 10, (char*) "%i", _player->GetLevel());
    
    glPopMatrix();
    
    
}


void UI::RenderKilledInfo()
{
    
    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.0);
    freetype::print(*(GetFont()), 10, 10, (char*) "Killed: %i", _player->GetEnemiesKilled());
    glPopMatrix();
    
}





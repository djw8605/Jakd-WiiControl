#include "MainMenu.h"
#include <GL/glut.h>
#include <stdio.h>
#include "display.h"
#include "FreeType/FreeType.h"
#include "config.h"
#include "ModelLoader/CModel3DS.h"

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
    gluPerspective(FOV, (GLfloat) width/ (GLfloat) height, 40, 5000.0);
    
    glMatrixMode(GL_MODELVIEW);
        

   m_model = new CModel3DS("snowman.3ds");
   m_model->CreateVBO();
    
}

void MainMenu::DeInit()
{
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    
}


void MainMenu::Render()
{
    DrawBackground();
    DrawMenu();
    
    
    
}

void MainMenu::Select(int x, int y)
{
    
    
    
}

void MainMenu::Reshape(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    m_w = w;
    m_h = h;
    
    glMatrixMode(GL_MODELVIEW);
    
}

void MainMenu::DrawBackground()
{
    
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
        glLoadIdentity();
        glViewport(0, 0, (GLsizei) m_w, (GLsizei) m_h);
        gluPerspective(FOV, (GLfloat) m_w/ (GLfloat) m_h, 40, 5000.0);
        
        glMatrixMode(GL_MODELVIEW);
    
        glPushMatrix();
            


           glLoadIdentity();
            gluLookAt(0.0, -30.0, 100.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
            glPushMatrix();
            
            
            glTranslatef(0, 0, 0);
            glColor4f(1.0, 1.0, 1.0, 1.0);
            
          /*  glBegin(GL_LINES);
            glVertex3f(-1000, 0, 0);
            glVertex3f(1000, 0, 0);
            
            glVertex3f(0.0, -1000, 0);
            glVertex3f(0.0, 1000, 0);
            
            glVertex3f(0.0, 0.0, -1000);
            glVertex3f(0.0, 0.0, 1000);
            glEnd();
            */
        /*    glBegin(GL_LINES);
            for(int i = -500; i < 500; i+=10) {
            glVertex3f(-1000, 0.0, i);
            glVertex3f(1000, 0.0, i);
            
            glVertex3f(i, -1000, 0.0);
            glVertex3f(i, 1000, 0.0);
            
            glVertex3f(0.0, i, -1000);
            glVertex3f(0.0, i, 1000);
            
            }
            
            glEnd();
           */ 
            static double angle = 0;
            angle += getTime() * 10.0;
            glRotatef(angle, 0.0, 1.0, 0.0);
            m_model->Draw();
            
            
            
            glPopMatrix();
            
            glPopMatrix();
    
    
}



void MainMenu::DrawMenu()
{
    
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        glViewport(0, 0, (GLsizei) m_w, (GLsizei) m_h);
        gluOrtho2D(0, 1000, 0, 1000);
        
        glMatrixMode(GL_MODELVIEW);
        glDisable(GL_LIGHTING);
        glEnable(GL_BLEND);
      
        glPushMatrix();
        glTranslatef(0, 0, 0);
        glColor4f(0.0, 0.0, 1.0, 0.5);
        glBegin(GL_QUADS);
        glVertex2f(100, 100);
        glVertex2f(900, 100);
        glVertex2f(900, 900);
        glVertex2f(100, 900);
        glEnd();
        
        glColor4f(1.0, 1.0, 1.0, 1.0);
        freetype::print(*(GetFont()), 0, 100, "Welcome to WiiControl Main Menu");
        
    
        glPopMatrix();
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
    
}




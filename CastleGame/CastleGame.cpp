#include "CastleGame.h"
#include <GL/glut.h>
#include "TextureLoader/CTargaImage.h"
#include "config.h"
#include "Cursor/WiiCursor.h"
#include "Camera/Camera.h"

#include <iostream>

using namespace std;


CastleGame::CastleGame()
{
    pillarTex = 0;
    CTargaImage image;
        if (!image.Load("Media/Stonetexture.tga"))
        {
            cerr << "Error opening Media/Stonetexture.tga" << endl;
        }
        else
        {

            glEnable(GL_TEXTURE_2D);
            glGenTextures(1, &pillarTex);

            glBindTexture(GL_TEXTURE_2D, pillarTex);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

            gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, image.GetWidth(), image.GetHeight(),
            GL_RGB, GL_UNSIGNED_BYTE, image.GetImage());

            image.Release();

        }
}

CastleGame::~CastleGame()
{
}



void CastleGame::Init()
{
    
    int width = glutGet(GLUT_WINDOW_WIDTH);
    int height = glutGet(GLUT_WINDOW_WIDTH);
    
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glViewport(0, 0, (GLsizei) width, (GLsizei) height);
    gluPerspective(FOV, (GLfloat) width/ (GLfloat) height, 40, 5000.0);
    
    glMatrixMode(GL_MODELVIEW);
    
    _camera->SetCameraLocation(0.0, -30.0, 10.0, 0.0, 0.0, 0.0);
        
    
}


void CastleGame::DeInit()
{
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    
}



void CastleGame::Render()
{
    _camera->positionCamera();
    DrawCastle();
    _cursor->Render();
    
    
}



void CastleGame::Select(int x, int y)
{
    
    
    
}


void CastleGame::Reshape(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    m_w = w;
    m_h = h;
    
    glMatrixMode(GL_MODELVIEW);
    
}


void CastleGame::DrawCastle()
{
    
    /* Render the pillar */
    glPushMatrix();
    
    if (!pillarTex)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, pillarTex);
    }
    
    /* Draw both sides */
    for (int i = 0; i < 2; i++)
    {
        
        if (i == 1)
            glScalef(1.0, -1.0, 1.0);

        glBegin(GL_QUADS);
        glColor4f(1.0, 0.0, 0.0, 1.0);
        
        /* For textures, the sides are sqrt(2) + sqrt(2) + 2 = 4.8284
         * Therefore:
         * sqrt(2) / 4.8284 =  .29289
         * 2 / 4.8284 = .41421
         * 
         * For the top, the total surface area of the top is:
         * sqrt(2) + 5 = 6.41421
         * Therefore:
         * 5/6.41421 = .7795
         * 
         */
        /* The three sides */
        glTexCoord2f(0.0, 0.0); glVertex3f(0.0, 0.0, 0.0);
        glTexCoord2f(0.0, 0.7795); glVertex3f(0.0, 0.0, 5.0);
        glTexCoord2f(0.29289, 0.7795); glVertex3f(1.0, -1.0, 5.0);
        glTexCoord2f(0.29289, 0.0); glVertex3f(1.0, -1.0, 0.0);

        glTexCoord2f(0.29289, 0.0); glVertex3f(1.0, -1.0, 0.0);
        glTexCoord2f(0.29289, 0.7795); glVertex3f(1.0, -1.0, 5.0);
        glTexCoord2f(0.70710, 0.7795); glVertex3f(3.0, -1.0, 5.0);
        glTexCoord2f(0.70710, 0.0); glVertex3f(3.0, -1.0, 0.0);

        glTexCoord2f(0.70710, 0.0); glVertex3f(3.0, -1.0, 0.0);
        glTexCoord2f(0.70710, 0.7795); glVertex3f(3.0, -1.0, 5.0);
        glTexCoord2f(1.0, 0.7795); glVertex3f(4.0, 0.0, 5.0);
        glTexCoord2f(1.0, 0.0); glVertex3f(4.0, 0.0, 0.0);
        
        /* Rectangle on top */
        glTexCoord2f(0.29289, 0.7795); glVertex3f(1.0, -1.0, 5.0);
        glTexCoord2f(0.29289, 1.0); glVertex3f(1.0, 0.0, 6.0);
        glTexCoord2f(0.70710, 1.0); glVertex3f(3.0, 0.0, 6.0);
        glTexCoord2f(0.70710, 0.7795); glVertex3f(3.0, -1.0, 5.0);
        
        glEnd();
        
        /* Triangle for the corners on top */
        glBegin(GL_TRIANGLES);
        
        glTexCoord2f(0.0, 0.7795); glVertex3f(0.0, 0.0, 5.0);
        glTexCoord2f(0.29289, 1.0); glVertex3f(1.0, 0.0, 6.0);
        glTexCoord2f(0.29289, 0.7795); glVertex3f(1.0, -1.0, 5.0);
        
        glTexCoord2f(0.70710, 0.7795); glVertex3f(3.0, -1.0, 5.0);
        glTexCoord2f(0.70710, 1.0); glVertex3f(3.0, 0.0, 6.0);
        glTexCoord2f(1.0, 0.7795); glVertex3f(4.0, 0.0, 5.0);
        
        glEnd();

    }
    
    if (!pillarTex)
        glDisable(GL_TEXTURE_2D);
    
    
    glPopMatrix();
    
    
    
}






#include "WiiCursor.h"
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "TextureLoader/CTargaImage.h"

#include <iostream>

using namespace std;

WiiCursor::WiiCursor()
{
    cursorTex = 0;
    CTargaImage image;
    if (!image.Load("/home/dweitzel/workspace/WiiControl/Media/crosshair.tga"))
    {
        cerr << "Error opening Media/crosshair.tga" << endl;
    }
    else
    {

        glEnable(GL_TEXTURE_2D);
        glGenTextures(1, &cursorTex);

        glBindTexture(GL_TEXTURE_2D, cursorTex);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, image.GetWidth(), image.GetHeight(),
        GL_RGB, GL_UNSIGNED_BYTE, image.GetImage());

        image.Release();

    }

}

WiiCursor::~WiiCursor()
{
    if (cursorTex)
        glDeleteTextures(1, &cursorTex);
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
    //glLoadIdentity();
    gluOrtho2D(0, 1024, 0, 768);

    glMatrixMode(GL_MODELVIEW);
    
    glPushMatrix();
    glDisable(GL_FOG);
    
    
    glTranslatef(cursorX, cursorY, 0.0);
    cout << "cursorX, cursorY: " << cursorX << ", " << cursorY << endl;
    
    /* If the cursor Texture is loaded and working */
    if (cursorTex != 0)
    {
        
        glBegin(GL_QUADS);
        glColor4f(0.0, 0.0, 1.0, 1.0);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, cursorTex);

        glTexCoord2f(0.0, 0.0);
        glVertex2f(-10.0, -10.0);

        glTexCoord2f(0.0, 1.0);
        glVertex2f(-10.0, 10.0);

        glTexCoord2f(1.0, 1.0);
        glVertex2f(10.0, 10.0);

        glTexCoord2f(1.0, 0.0);
        glVertex2f(10.0, -10.0);

        glDisable(GL_TEXTURE_2D);
        glEnd();

    } else {
        /* If the texture isn't working */
        glColor4f(0.0, 0.0, 1.0, 0.8);
        glBegin(GL_LINES);
        
        glVertex2f(-10.0, 0.0);
        glVertex2f(10.0, 0.0);
        
        glVertex2f(0.0, -10.0);
        glVertex2f(0.0, 10.0);
        
        
        glEnd();
        
        
        
        
    }
    
    glPopMatrix();
    glEnable(GL_FOG);
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






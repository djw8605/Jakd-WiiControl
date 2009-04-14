#include "CastleGame.h"
#include <GL/glut.h>
#include "TextureLoader/CTargaImage.h"
#include "config.h"
#include "Cursor/WiiCursor.h"
#include "Camera/Camera.h"
#include "CastleGame/UI.h"
#include "CastleGame/PlayerStats.h"
#include "CastleGame/Enemy.h"
#include "display.h"
#include "TextPrinter/BitMapText.h"
#include "CastleGame/Catapult.h"
#include "Audio/Audio.h"

#include <float.h>
#include <iostream>

using namespace std;

//#define PICKING_DEBUG

#ifdef PICKING_DEBUG
void AddLine(point p1, point p2);
void RenderLines();
#endif

CastleGame::CastleGame()
{
    pillarTex = 0;
    CTargaImage image;
        if (!image.Load("Media/stone-texture.tga"))
        {
            cerr << "Error opening Media/stone-texture.tga" << endl;
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
        if (!image.Load("Media/field.tga"))
                {
                    cerr << "Error opening Media/field.tga" << endl;
                }
                else
                {

                    glEnable(GL_TEXTURE_2D);
                    glGenTextures(1, &fieldTex);

                    glBindTexture(GL_TEXTURE_2D, fieldTex);

                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

                    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, image.GetWidth(), image.GetHeight(),
                    GL_RGB, GL_UNSIGNED_BYTE, image.GetImage());

                    image.Release();

                }


        groundList = glGenLists(1);
        glNewList(groundList, GL_COMPILE);

        glBegin(GL_QUADS);

        for(int i = -1000; i < 1000; i+=200)
        {

                glNormal3f(0.0, 0.0, 1.0); glTexCoord2f(0.0, 0.0); glVertex3f((GLfloat)i, 0.0, 0.0);
                glNormal3f(0.0, 0.0, 1.0); glTexCoord2f(0.0, 1.0); glVertex3f((GLfloat)i, 2000.0, 0.0);
                glNormal3f(0.0, 0.0, 1.0); glTexCoord2f(1.0, 1.0); glVertex3f((GLfloat)i+200, 2000.0, 0.0);
                glNormal3f(0.0, 0.0, 1.0); glTexCoord2f(1.0, 0.0); glVertex3f((GLfloat)i+200, 0.0, 0.0);


        }

        glEnd();

        glEndList();

        m_numEnemies = 10;
        m_enemies = new Enemy[m_numEnemies];
        m_picking = 0;


        /* Audio Testing */
        //_audio->PlaySound("Media/Arrow_Swoosh.wav");


}

CastleGame::~CastleGame()
{
    for(int i =0; i < m_numEnemies; i++)
        delete (m_enemies+i);

    glDeleteTextures(1, &pillarTex);
    glDeleteTextures(1, &fieldTex);
    glDeleteLists(groundList, 1);
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

    _camera->SetCameraLocation(0.0, -3.0, 53.0, 0.0, 1000.0, 0.0);
    glEnable(GL_BLEND);


    glEnable(GL_FOG);
    float fogStart = 1000.0, fogEnd = 3000.0;
    float fogColor[4] = { 0.8, 0.8, 0.8, 0.1 };
    glFogf(GL_FOG_DENSITY, 0.002f);
    glFogi(GL_FOG_MODE, GL_EXP);
    glFogf(GL_FOG_START, fogStart);
    glFogf(GL_FOG_END, fogEnd);
    glFogfv(GL_FOG_COLOR, fogColor);

    GLfloat position[] = { 100.0, 100.0, 1000.0, 1.0 };
    GLfloat ambient[] = { 0.5, 0.5, 0.5, 1.0 };
      GLfloat diffuse[] = { 1, 1, 1, 1.0 };

      glLightfv (GL_LIGHT0, GL_POSITION, position);
        glLightfv (GL_LIGHT0, GL_DIFFUSE, diffuse);
        glLightfv (GL_LIGHT0, GL_SPECULAR, diffuse);
        glLightfv (GL_LIGHT0, GL_AMBIENT, ambient);

        glEnable(GL_LIGHTING);
          glEnable(GL_LIGHT0);

          glEnable(GL_NORMALIZE);
            glEnable(GL_AUTO_NORMAL);


            glEnable(GL_BLEND);
            glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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

    glPushName(1000);
    DrawCastle();
    glPopName();

#ifdef PICKING_DEBUG
    RenderLines();
#endif // PICKING_DEBUG
    //glPushName(1001);
    DrawGround();
    //glPopName();

    _catapult->Render();

    float timeDiff = getTime();
    if (m_picking)
        timeDiff = 0.0;

    for (int i = 0; i < m_numEnemies; i++)
    {
        glPushName(i);
        m_enemies[i].Render(timeDiff);
        glPopName();

        if(!m_picking)
        {
            if(m_enemies[i].GetY() < 0.0)
            {
                m_enemies[i].ReInit();

                /* Take health away from the player */
                _player->AffectWallHealth(-10.0);
                _player->IncrementEnemiesNotKilled();
            }

        }
    }


    if(!m_picking) {
        _cursor->Render(m_w, m_h);
        _ui->Render();
    }



}



void CastleGame::Select(int x, int y)
{
    /* Testing */

    _audio->PlaySound("Media/Arrow_Swoosh2.wav");
    ray r;
    GLdouble pos3D_x, pos3D_y, pos3D_z;

    glLoadIdentity();
    // arrays to hold matrix information
    _camera->positionCamera();
    GLdouble model_view[16];
    glGetDoublev(GL_MODELVIEW_MATRIX, model_view);

    GLdouble projection[16];
    glGetDoublev(GL_PROJECTION_MATRIX, projection);

    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);

    // get 3D coordinates based on window coordinates

    gluUnProject(x, y, 0.0001,
            model_view, projection, viewport,
            &pos3D_x, &pos3D_y, &pos3D_z);

    r.origin.x = (float)pos3D_x;
    r.origin.y = (float)pos3D_y;
    r.origin.z = (float)pos3D_z;

    //printf("%lf, %lf, %lf\n", r.origin.x, r.origin.y, r.origin.z);
    gluUnProject(x, y, 1.00,
             model_view, projection, viewport,
             &pos3D_x, &pos3D_y, &pos3D_z);
    //printf("%lf, %lf, %lf\n", pos3D_x, pos3D_y, pos3D_z);

    //ray r;
    r.direction.x = (float)pos3D_x - r.origin.x;
    r.direction.y = (float)pos3D_y - r.origin.y;
    r.direction.z = (float)pos3D_z - r.origin.z;

    /* Debugging stuff */
#ifdef PICKING_DEBUG
    point p;
    p.x = (float)pos3D_x;
    p.y = (float)pos3D_y;
    p.z = (float)pos3D_z;
    AddLine(r.origin, p);
#endif //PICKING_DEBUG

    //printf("Ray, o = (%lf, %lf, %lf), d = (%lf, %lf, %lf)\n", r.origin.x, r.origin.y, r.origin.z, r.direction.x, r.direction.y, r.direction.z);
    float distance = FLT_MAX;
    int minIndex = -1;
    float tmpDistance = 0.0;
    for(int i = 0; i < m_numEnemies; i++)
    {
        tmpDistance = m_enemies[i].DoIntersect(r);
        if((tmpDistance < distance) && (tmpDistance != 0.0))
        {
            distance = tmpDistance;
            minIndex = i;
        }

    }
    //printf("Distance = %lf\n", distance);
    if((distance != 0.0) && (minIndex != -1))
    {
        //printf("Killed %i\n", minIndex);
        m_enemies[minIndex].ReInit();
               _player->IncrementEnemiesKilled();
               if((_player->GetEnemiesKilled() > 0) && ((_player->GetEnemiesKilled() % 20) == 0))
               {
                   _player->IncrementLevel();
               }
    }

    return;
    /* Now the wonders of opengl picking, ugh... */
    //printf("Selected: %i, %i\n", x, y);
    m_picking = 1;

    glPushMatrix();
    GLuint buffer[512];
    //GLint viewport[4];



    glSelectBuffer(512, buffer);
    glRenderMode(GL_SELECT);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glGetIntegerv(GL_VIEWPORT,viewport);
    gluPickMatrix(x, y, 5, 5, viewport);

    gluPerspective(FOV, (float)glutGet(GLUT_WINDOW_WIDTH) / (float)glutGet(GLUT_WINDOW_HEIGHT), 40, 5000.0);


    glMatrixMode(GL_MODELVIEW);
    glInitNames();
    glDisable(GL_LIGHTING);
    glDisable(GL_FOG);
    this->Render();
    glEnable(GL_LIGHTING);
    glEnable(GL_FOG);

    int hits = glRenderMode(GL_RENDER);
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    unsigned int min = 0xFFFFFFFF;
    int i = 0;
    int checked = 0;
    int selected = 0;

   // printf("Hits = %i\n", hits);

  //  if (hits)
    //    selected = buffer[3];
    //else
     //   selected = -1;

    selected = -1;


  /*  printf("hits = %i\n", hits);
            printf("buffer0 = %u\n", buffer[0]);
            printf("buffer1 = %u\n", buffer[1]);
            printf("buffer2 = %u\n", buffer[2]);
            printf("buffer3 = %u\n", buffer[3]);
            printf("buffer4 = %u\n", buffer[4]);
            printf("buffer5 = %u\n", buffer[5]);
            printf("buffer6 = %u\n", buffer[6]);
            printf("buffer6 = %u\n", buffer[7]);
            printf("buffer6 = %u\n", buffer[8]);
            printf("buffer6 = %u\n", buffer[9]);
*/

    while(checked < hits) {
                    //printf("Checking %i\n", buffer[i]);
                    if(buffer[i] == 0) {
                          //printf("0 hits = %i\n", buffer[i]);
                            checked++;
                            i += 3;
                            continue;
                    }
                    i++;
                    //printf("Comparing %i and %i", min, buffer[i]);
                    if(min > buffer[i]) {
                          //printf("found min = %i, to %i\n", buffer[i], buffer[i+2]);
                          //fflush(stdout);
                            min = buffer[i];
                            i+=2;
                            selected = buffer[i];
                            i++;
                            checked++;
                    } else {
                    i+=3;
                    checked++;
                    }
            }

    if (selected != -1)
    {
        //printf("Selected enemy: %i\n", selected);

        m_enemies[selected].ReInit();
        _player->IncrementEnemiesKilled();
        if((_player->GetEnemiesKilled() > 0) && ((_player->GetEnemiesKilled() % 20) == 0))
        {
            _player->IncrementLevel();
        }
    }


    m_picking = 0;
    //printf("New Health: %lf\n", _player->GetPlayerHealth());
}


void CastleGame::Reshape(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    gluPerspective(FOV, (GLfloat) w/ (GLfloat) h, 0.1, 5000.0);
    m_w = w;
    m_h = h;

    glMatrixMode(GL_MODELVIEW);

}


void CastleGame::DrawCastle()
{
    glPushMatrix();
    glPushMatrix();
    glTranslatef(0.0, 0.0, 50.0);
    DrawPillar();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-10.0, 0.0, 50.0);
    DrawPillar();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(10, 0.0, 50.0);
    DrawPillar();
    glPopMatrix();
    glPopMatrix();


    DrawWall();

}

void CastleGame::DrawPillar()
{


    /* Render the pillar */
    glPushMatrix();

    //glTranslatef(0.0, 0.0, 100.0);
    //glScalef(3.0, 3.0, 3.0);

    GLfloat bodyamb[] = { .5, .5, .5, 1 };
              GLfloat bodydif[] = { .8, .8, .8, 1 };
              GLfloat bodyspec[] = { .8, .8, .8, 1 };

              glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, bodyamb);
                glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, bodydif);
                glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, bodyspec);

    if (pillarTex)
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
        glColor4f(1.0, 1.0, 1.0, 0.0);



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
        glNormal3f(-1.0, -1.0, 0.0); glTexCoord2f(0.0, 0.0); glVertex3f(0.0, 0.0, 0.0);
        glNormal3f(-1.0, -1.0, 0.0); glTexCoord2f(0.0, 0.7795); glVertex3f(0.0, 0.0, 5.0);
        glNormal3f(-1.0, -1.0, 0.0); glTexCoord2f(0.29289, 0.7795); glVertex3f(1.0, -1.0, 5.0);
        glNormal3f(-1.0, -1.0, 0.0); glTexCoord2f(0.29289, 0.0); glVertex3f(1.0, -1.0, 0.0);

        glNormal3f(0.0, -1.0, 0.0); glTexCoord2f(0.29289, 0.0); glVertex3f(1.0, -1.0, 0.0);
        glNormal3f(0.0, -1.0, 0.0); glTexCoord2f(0.29289, 0.7795); glVertex3f(1.0, -1.0, 5.0);
        glNormal3f(0.0, -1.0, 0.0); glTexCoord2f(0.70710, 0.7795); glVertex3f(3.0, -1.0, 5.0);
        glNormal3f(0.0, -1.0, 0.0); glTexCoord2f(0.70710, 0.0); glVertex3f(3.0, -1.0, 0.0);

        glNormal3f(1.0, -1.0, 0.0); glTexCoord2f(0.70710, 0.0); glVertex3f(3.0, -1.0, 0.0);
        glNormal3f(1.0, -1.0, 0.0); glTexCoord2f(0.70710, 0.7795); glVertex3f(3.0, -1.0, 5.0);
        glNormal3f(1.0, -1.0, 0.0); glTexCoord2f(1.0, 0.7795); glVertex3f(4.0, 0.0, 5.0);
        glNormal3f(1.0, -1.0, 0.0); glTexCoord2f(1.0, 0.0); glVertex3f(4.0, 0.0, 0.0);

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

    if (pillarTex)
        glDisable(GL_TEXTURE_2D);


    glPopMatrix();



}


void CastleGame::DrawWall()
{

    glPushMatrix();

    GLfloat bodyamb[] = { .6, .6, .6, 1 };
              GLfloat bodydif[] = { .6, .6, .6, 1 };
              GLfloat bodyspec[] = { .8, .8, .8, 1 };

              glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, bodyamb);
                glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, bodydif);
                glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, bodyspec);

    if (pillarTex)
        {
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, pillarTex);
        }

    glBegin(GL_QUADS);

    /* Top of the wall */
    glNormal3f(0.0, 0.0, 1.0); glTexCoord2f(0.0, 0.0); glVertex3f(-20, -20, 50);
    glNormal3f(0.0, 0.0, 1.0); glTexCoord2f(0.0, 0.7); glVertex3f(-20, 0, 50);
    glNormal3f(0.0, 0.0, 1.0); glTexCoord2f(1.0, 0.7); glVertex3f(20, 0,  50);
    glNormal3f(0.0, 0.0, 1.0); glTexCoord2f(1.0, 0.0); glVertex3f(20, -20, 50);


    glEnd();

    if (pillarTex)
           glDisable(GL_TEXTURE_2D);

    glPopMatrix();

}


void CastleGame::DrawGround()
{

    glPushMatrix();

    GLfloat bodyamb[] = { .6, .6, .6, 1 };
              GLfloat bodydif[] = { .6, .6, .6, 1 };
              GLfloat bodyspec[] = { .6, .6, .6, 1 };

              glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, bodyamb);
                glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, bodydif);
                glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, bodyspec);

    if (fieldTex)
        {
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, fieldTex);
        }

    glColor4f(1.0, 1.0, 1.0, 1.0);


    glCallList(groundList);


    if (fieldTex)
            glDisable(GL_TEXTURE_2D);


    glPopMatrix();




}


void CastleGame::Reset()
{
	for(int i = 0; i < m_numEnemies; i++)
		m_enemies[i].ReInit();

	_catapult->Reinit();

	_player->Reset();


}


#ifdef PICKING_DEBUG


typedef struct _dualpoints
{
    point p1;
    point p2;
    _dualpoints* next;
} dualpoints;


dualpoints* head = NULL;

void AddLine(point p1, point p2)
{
    if(head == NULL)
    {
        head = new dualpoints;
        head->p1 = p1;
        head->p2 = p2;
        head->next = 0;
    } else {

        dualpoints* tmp = head;
        while(tmp->next != NULL)
            tmp = tmp->next;
        tmp->next = new dualpoints;
        tmp->next->p1 = p1;
        tmp->next->p2 = p2;
        tmp->next->next = 0;

    }

}

void RenderLines()
{
    dualpoints* tmp = head;
    glPushMatrix();

    GLfloat bodyamb[] = { 1.0, 1.0, 0.0, 1.0 };
    GLfloat bodydif[] = { 1.0, 1.0, 0.0, 1.0 };
    GLfloat bodyspec[] = { 1.0, 1.0, 0.0, 1.0 };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, bodyamb);
      glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, bodydif);
      glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, bodyspec);

    glBegin(GL_LINES);

    while(tmp != 0)
    {
        glVertex3f(tmp->p1.x, tmp->p1.y, tmp->p1.z);
        glVertex3f(tmp->p2.x, tmp->p2.y, tmp->p2.z);
        tmp = tmp->next;
    }
    glEnd();
    glPopMatrix();

}


#endif // PICKING_DEBUG



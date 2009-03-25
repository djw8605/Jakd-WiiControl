#include <cstdlib>
#include <GL/glut.h>
#include "Enemy.h"
#include <cstdio>
#include "CastleGame/PlayerStats.h"
#include "Math/Math.h"

Enemy::Enemy()
{
    this->ReInit();
    
    m_model = _player->GetEnemyModel();

    /* For intersection points */
    //m_p[0].x = 20.0;
    m_p[0].y = 0.0;
    m_p[0].z = 0.0;

   //m_p[1].x = 20.0;
    m_p[1].y = 0.0;
    m_p[1].z = 25.0;

    //m_p[2].x = 30.0;
    m_p[2].y = 0.0;
    m_p[2].z = 25.0;

    //m_p[3].x = 30.0;
    m_p[3].y = 0.0;
    m_p[3].z = 0.0;


}

Enemy::~Enemy()
{
    printf("Enemy Deleted\n");
    delete m_model;
}

void Enemy::Render(float timeDiff)
{
    
    
    glPushMatrix();
    //glLoadIdentity();
    /* Calculate new Y position */
    GLfloat bodyamb[] = { 1.0, 0.0, 0.0, 1.0 };
    GLfloat bodydif[] = { 1.0, 0.0, 0.0, 1.0 };
    GLfloat bodyspec[] = { 1.0, 0.0, 0.0, 1.0 };
                  

    
    m_y -= timeDiff * ENEMY_SPEED * LevelSpeed[_player->GetLevel()-1];

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, bodyamb);
      glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, bodydif);
      glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, bodyspec);
    //glLoadIdentity();
    glTranslatef(m_x, m_y, 0.0);
/*    glBegin(GL_QUADS);
    glVertex3f(20.0, 0.0, 0.0);
    glVertex3f(20.0, 0.0, 25.0);
    glVertex3f(30.0, 0.0, 25.0);
    glVertex3f(30.0, 0.0, 0.0);
    glEnd();
   */ 
    //glRotatef(90, 1.0, 0.0, 0.0);
    glScalef(0.03, 0.03, 0.03);
    glColor4f(1.0, 0.0, 0.0, 1.0);
    
    //printf("pos = %lf\n", m_y);
    m_model->Draw();

    
    
    /*
    glBegin(GL_QUADS);
    glVertex3f(-5.0, 0.0, 0.0);
    glVertex3f(-5.0, 0.0, 10.0);
    glVertex3f(5.0, 0.0, 10.0);
    glVertex3f(5.0, 0.0, 0.0);
    glEnd();
    */
    
    
    glPopMatrix();
    
    
    
}


void Enemy::ReInit()
{
    /* Generate a decent random number between 0 and the variance */
    float random = (float)(rand() % (MAX_ENEMY_VARIANCE * 10));
    random = random / 10.0;

    /* Translate the random number to a point centered around x = 0 */;
    random = random - (MAX_ENEMY_VARIANCE / 2);
    
    m_x = random;
    m_y = (float)(rand() % 1000) + ENEMY_STARTING_Y;
    
    m_p[0].x = m_p[1].x = 20 + m_x;
    m_p[2].x = m_p[3].x = 30 + m_x;

    
    
}

float Enemy::GetY()
{
    
    return this->m_y;
}


float Enemy::DoIntersect(const ray &r)
{
    //printf("y = %lf\n", m_y); 
    m_p[0].y = m_p[1].y = m_p[2].y = m_p[3].y = m_y;

    
    return Intersect(r, m_p[0], m_p[1], m_p[2], m_p[3]);
    
    
    
    
}



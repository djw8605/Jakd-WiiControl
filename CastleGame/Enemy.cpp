#include <cstdlib>
#include <GL/glut.h>
#include "Enemy.h"
#include <cstdio>
#include "CastleGame/PlayerStats.h"

Enemy::Enemy()
{
    this->ReInit();
    
    m_model = _player->GetEnemyModel();

}

Enemy::~Enemy()
{
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
    glColor4f(1.0, 0.0, 0.0, 1.0);
    
    printf("Drawing: %p\n", m_model);
    //m_model->Draw();
    printf("done drawing\n");
    
    
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
    

    
    
}

float Enemy::GetY()
{
    
    return this->m_y;
}


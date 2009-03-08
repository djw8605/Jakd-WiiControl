#include "Catapult.h"
#include "display.h"
#include <GL/glut.h>
#include <cmath>

#define CATAPULT_SPEED 200.0
#define SPHERE_SIZE 7.0
#define eqn(x) 70*cos((x-375)/500)

Catapult::Catapult()
{
    pos[0] = 0.0;
    pos[1] = 3000.0;
    pos[2] = 0.0;
}

Catapult::~Catapult()
{
}

Catapult* Catapult::GetInstance()
{
    static Catapult* instance = new Catapult();
    return instance;
}


void Catapult::Render()
{
    
    GLfloat bodyamb[] = { 0.2, 0.2, 0.2, 1.0 };
       GLfloat bodydif[] = { 0.2, 0.2, 0.2, 1.0 };
       GLfloat bodyspec[] = { 0.2, 0.2, 0.2, 1.0 };
    
    glPushMatrix();

    pos[0] = 0;
    pos[1] = pos[1] - getTime()*CATAPULT_SPEED;
    pos[2] = eqn(pos[1]);

    glTranslatef(pos[0], pos[1], pos[2]);
    
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, bodyamb);
          glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, bodydif);
          glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, bodyspec);
    
    glutSolidSphere(SPHERE_SIZE, 10, 10);
    
    glPopMatrix();
}


void Catapult::GetCurrentPos(float* buf)
{
    buf[0] = pos[0];
    buf[1] = pos[1];
    buf[2] = pos[2];
    
}


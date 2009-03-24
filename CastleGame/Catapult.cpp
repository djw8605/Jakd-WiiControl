#include "Catapult.h"
#include "display.h"
#include <GL/glut.h>
#include <cmath>
#include "Camera/Camera.h"
#include "CastleGame/PlayerStats.h"

#define CATAPULT_SPEED 200.0
#define SPHERE_SIZE 7.0
#define eqn(x) 70*cos((x-375)/500)
#define CATAPULT_START 3000.0
#define CATAPULT_DMG -50.0

float CatapultOften[] = { 10.0, 8.0, 7.0, 6.0 };

Catapult::Catapult()
{
    pos[0] = 0.0;
    pos[1] = CATAPULT_START;
    pos[2] = 0.0;
    counter = 0.0;
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
    
    /* Check if we should even render the catapult */
    counter -= getTime();
    if(counter > 0)
        return;
    
    /* Ok, check if it's hitting the wall now */
    //printf("%lf\n", pos[1]);
    if(pos[1] <= 0.0)
    {
        float camPos[3];
        _camera->GetPosition(camPos);


        if(camPos[0] <= 0)
        {
            _camera->ShakeCamera(1.0);
            _player->AffectPlayerHealth(CATAPULT_DMG);
        }
        
        counter = CatapultOften[_player->GetLevel()];
        pos[1] = CATAPULT_START;
        
    }
    
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


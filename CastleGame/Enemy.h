#ifndef ENEMY_H_
#define ENEMY_H_

#include "Math/Math.h"
#include "ModelLoader/CModel3DS.h"

#define MAX_ENEMY_VARIANCE 400             /* How wide the area that enemies can be made */
#define ENEMY_SPEED 50.0                                 /* Larger = faster */
#define ENEMY_STARTING_Y 2000.0                /* Starting y position, how far away from the castle */

static const float LevelSpeed []  = { 1.0, 1.25, 1.50, 1.75, 2.0 };


class Enemy
{
public:
	Enemy();
	virtual ~Enemy();
	void Render(float timeDiff);
	void ReInit();
	float GetY();
	float DoIntersect(const ray &r);
	
private:
    float m_x, m_y;
    CModel3DS* m_model;
    point m_p[4];
    
};

#endif /*ENEMY_H_*/

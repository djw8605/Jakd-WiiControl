#ifndef ENEMY_H_
#define ENEMY_H_

#define MAX_ENEMY_VARIANCE 400             /* How wide the area that enemies can be made */
#define ENEMY_SPEED 50.0                                 /* Larger = faster */
#define ENEMY_STARTING_Y 2000.0                /* Starting y position, how far away from the castle */

static const float LevelSpeed []  = { 1.0, 1.25, 1.50, 1.75 };


class Enemy
{
public:
	Enemy();
	virtual ~Enemy();
	void Render(float timeDiff);
	void ReInit();
	float GetY();
	
private:
    float m_x, m_y;
    
};

#endif /*ENEMY_H_*/

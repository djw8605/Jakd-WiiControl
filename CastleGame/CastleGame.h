#ifndef CASTLEGAME_H_
#define CASTLEGAME_H_

#include <GL/glut.h>
#include <GL/gl.h>

#include "AbstractScene/AbstractScene.h"
#include "CastleGame/Enemy.h"

class CastleGame : public AbstractScene
{
public:
    CastleGame();
    virtual ~CastleGame();
    virtual void Render(); /* Render the scene */
    virtual void Init(); /* Initialize the scene */
    virtual void DeInit(); /* DeInitialize the scene */
    virtual void Select(int x, int y); /* Select a portion of the screen, such as a mouse click */
    virtual void Reshape(int w, int h);
    
private:
    void DrawCastle();
    void DrawPillar();
    void DrawGround();
    void DrawWall();
    
    int m_w, m_h;
    
    GLuint pillarTex, fieldTex;
    GLuint groundList;
    Enemy* m_enemies;
    int m_numEnemies;
    int m_picking;
};

#endif /*CASTLEGAME_H_*/

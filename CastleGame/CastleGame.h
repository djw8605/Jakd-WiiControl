#ifndef CASTLEGAME_H_
#define CASTLEGAME_H_

#include "AbstractScene/AbstractScene.h"

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
    
    
};

#endif /*CASTLEGAME_H_*/

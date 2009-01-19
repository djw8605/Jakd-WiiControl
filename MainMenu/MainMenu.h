#ifndef MAINMENU_H_
#define MAINMENU_H_

#include "AbstractScene/AbstractScene.h"
#include "ModelLoader/CModel3DS.h"


class MainMenu : public AbstractScene
{
public:
	MainMenu();
	virtual ~MainMenu();
	virtual void Render();                 /* Render the scene */
	virtual void Init();                   /* Initialize the scene */
	virtual void DeInit();                 /* DeInitialize the scene */
	virtual void Select(int x, int y);     /* Select a portion of the screen, such as a mouse click */
	virtual void Reshape(int w, int h);    /* Reshape function */

private:
    void DrawBackground();
    void DrawMenu();
    
    
    int m_w;
    int m_h;
    
    CModel3DS* m_model;

};

#endif /*MAINMENU_H_*/

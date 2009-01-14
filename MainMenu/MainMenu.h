#ifndef MAINMENU_H_
#define MAINMENU_H_

#include "AbstractScene/AbstractScene.h"

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
};

#endif /*MAINMENU_H_*/

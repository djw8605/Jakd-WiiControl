#ifndef ABSTRACTSCENE_H_
#define ABSTRACTSCENE_H_

class AbstractScene
{
public:
	AbstractScene();
	virtual ~AbstractScene();
	virtual void Render();                 /* Render the scene */
	virtual void Init();                   /* Initialize the scene */
	virtual void DeInit();                 /* DeInitialize the scene */
	virtual void Select(int x, int y);     /* Select a portion of the screen, such as a mouse click */
	
};

#endif /*ABSTRACTSCENE_H_*/

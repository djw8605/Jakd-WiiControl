#ifndef UI_H_
#define UI_H_

class UI
{
public:
	UI();
	virtual ~UI();
	void Render();
	
private:
    void RenderHealthBar();
    void RenderWallHealth();
};



#endif /*UI_H_*/

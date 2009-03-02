#ifndef UI_H_
#define UI_H_

#define _ui UI::GetInstance()

class UI
{
public:
	UI();
	virtual ~UI();
	void Render();
	static UI* GetInstance();
	
private:
    void RenderHealthBar();
    void RenderWallHealth();
    void DrawBar(float healthPerc, char* inside);
    void RenderLevelInfo();
};



#endif /*UI_H_*/

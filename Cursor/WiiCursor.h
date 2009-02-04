#ifndef WIICURSOR_H_
#define WIICURSOR_H_


#include <GL/gl.h>

#define _cursor WiiCursor::GetInstance()

class WiiCursor
{
public:
	WiiCursor();
	virtual ~WiiCursor();
	static WiiCursor* GetInstance();
	void ProcessCoordinates(short x1, short y1, short x2, short y2);
	void Render();
	
private:
    float cursorX;
    float cursorY;
    GLuint cursorTex;
};

#endif /*WIICURSOR_H_*/

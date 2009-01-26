#ifndef WIICURSOR_H_
#define WIICURSOR_H_

#define _cursor Cursor::GetInstance()

class WiiCursor
{
public:
	WiiCursor();
	virtual ~WiiCursor();
	static WiiCursor* GetInstance();
	void SetCoordinates(short x, short y);
};

#endif /*WIICURSOR_H_*/

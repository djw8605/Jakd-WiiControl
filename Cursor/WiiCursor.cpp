#include "WiiCursor.h"

WiiCursor::WiiCursor()
{
}

WiiCursor::~WiiCursor()
{
}


WiiCursor* WiiCursor::GetInstance()
{
    
    static WiiCursor* cursor = new WiiCursor();
    return cursor;
    
    
}


void WiiCursor::SetCoordinates(short x, short y)
{
    
    /* Do a bunch of calculations to find the on screen coordinates */
    
    
}






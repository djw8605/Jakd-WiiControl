

#include "WiiInterface.h"
#include "wiiuse.h"

#define MAX_WIIMOTES 2
wiimote** wiimotes;


void StartWiiMotes()
{
	
	/* Initialize wiiuse */
	wiimotes = wiiuse_init(MAX_WIIMOTES)
	
	
}



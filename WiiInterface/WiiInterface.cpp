

#include "WiiInterface.h"
#include "wiiuse.h"
#include "Camera/Camera.h"

#define MAX_WIIMOTES 2
wiimote** wiimotes;


void StartWiiMotes()
{
	
	/* Initialize wiiuse */
	wiimotes = wiiuse_init(MAX_WIIMOTES);
	
	
}


void handle_event(struct wiimote_t* wm)
{
	if (IS_PRESSED(wm, WIIMOTE_BUTTON_A))
        printf("A pressed\n");
    if (IS_PRESSED(wm, WIIMOTE_BUTTON_B))
        printf("B pressed\n");
    if (IS_PRESSED(wm, WIIMOTE_BUTTON_UP))
    {
        printf("UP pressed\n");
    }
    if (IS_PRESSED(wm, WIIMOTE_BUTTON_DOWN))
    {
        printf("DOWN pressed\n");
    }
    if (IS_PRESSED(wm, WIIMOTE_BUTTON_LEFT))
        printf("LEFT pressed\n");
    if (IS_PRESSED(wm, WIIMOTE_BUTTON_RIGHT))
        printf("RIGHT pressed\n");
    if (IS_PRESSED(wm, WIIMOTE_BUTTON_MINUS))
        printf("MINUS pressed\n");
    if (IS_PRESSED(wm, WIIMOTE_BUTTON_PLUS))
        printf("PLUS pressed\n");
    if (IS_PRESSED(wm, WIIMOTE_BUTTON_ONE))
        printf("ONE pressed\n");
    if (IS_PRESSED(wm, WIIMOTE_BUTTON_TWO))
        printf("TWO pressed\n");
    if (IS_PRESSED(wm, WIIMOTE_BUTTON_HOME))
        printf("HOME pressed\n");

    if (IS_JUST_PRESSED(wm, WIIMOTE_BUTTON_MINUS))
        wiiuse_set_ir(wm, 0);

    if (IS_JUST_PRESSED(wm, WIIMOTE_BUTTON_PLUS))
        wiiuse_set_ir(wm, 1);
	
	
	
}


void WiiMotesInstalled()
{
	
	for (int i = 0; i < MAX_WIIMOTES; i++) 
	{
	  wiiuse_set_ir(wiimotes[i], 1);
	}
	
}


void ProcessPlayerLocation()
{
    /*
     * Process the player's location from the mounted wiimote
     */
    
    /* Need at least 2 visible IR Dots */
    if(wiimotes[0]->ir.dot[0].visible && wiimotes[0]->ir.dot[1].visible)
    {
        short dot1x = wiimotes[0]->ir.dot[0].rx;
        short dot1y = wiimotes[0]->ir.dot[0].ry;
        short dot2x = wiimotes[0]->ir.dot[1].rx;
        short dot2y = wiimotes[0]->ir.dot[1].ry;
        
        camera->ProcessCoordinates(dot1x, dot1y, dot2x, dot2y);
        
    } else {
        return;
    }
    
    
}

void ProcessWiiEvents()
{
    /* 
     *  Used to process events from the wii
     */
    
    if (wiiuse_poll(wiimotes, MAX_WIIMOTES))
    {
        int i = 0;
        for (; i< MAX_WIIMOTES; i++)
        {
            switch (wiimotes[i]->event)
            {
            case WIIUSE_EVENT:
                handle_event(wiimotes[i]);
                break;
            case WIIUSE_READ_DATA:
            case WIIUSE_NONE:
            case WIIUSE_STATUS:
            case WIIUSE_CONNECT:
            case WIIUSE_DISCONNECT:
            case WIIUSE_UNEXPECTED_DISCONNECT:
            case WIIUSE_NUNCHUK_INSERTED:
            case WIIUSE_NUNCHUK_REMOVED:
            case WIIUSE_CLASSIC_CTRL_INSERTED:
            case WIIUSE_CLASSIC_CTRL_REMOVED:
            case WIIUSE_GUITAR_HERO_3_CTRL_INSERTED:
            case WIIUSE_GUITAR_HERO_3_CTRL_REMOVED:
                break;
            }

        }

    }
	
	
    ProcessPlayerLocation();
	
}



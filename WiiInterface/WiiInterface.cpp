

#include <unistd.h>
#include <iostream>

#include "WiiInterface.h"
#include "wiiuse.h"
#include "Camera/Camera.h"
#include "Cursor/WiiCursor.h"

#define MAX_WIIMOTES 2
wiimote** wiimotes;
int numConnectedMotes = 0;
bool detecting = false;
int playerWiiIndex = 0;


void WiiMotesInstalled();

void SetWiiMoteLights()
{
    
    wiiuse_set_leds(wiimotes[playerWiiIndex], WIIMOTE_LED_1);
    wiiuse_set_leds(wiimotes[!playerWiiIndex], WIIMOTE_LED_2);
    
    
}



void StartWiiMotes()
{

	/* Initialize wiiuse */
	wiimotes = wiiuse_init(MAX_WIIMOTES);
	
	/* Goal: to connect the 2 wiimotes, and determine which is in the player's hand */
    int foundWiimotes = 0;
    do
    {
        std::cout << "Please Press the reset button on the wiimotes now" << std::endl;
        fflush(stdout);

        foundWiimotes = wiiuse_find(wiimotes, MAX_WIIMOTES, 5);

        if (foundWiimotes != 2)
        {
            std::cout << "Found " << foundWiimotes << std::endl;
            std::cout << "Did not find 2 wiimotes, retrying..." << std::endl;
            fflush(stdout);
        }

    } while (foundWiimotes != 2);
    
    int connected = wiiuse_connect(wiimotes, MAX_WIIMOTES);
    
    if(connected != MAX_WIIMOTES) 
    {
        std::cout << "Unable to connect to wiimotes" << std::endl;
    }
    
    numConnectedMotes = connected;
    
    /* Now determine which is in the player's hand */
    std::cout << "Please press the A button on your wiimote..." << std::endl;
   detecting = true;
    do 
    {
        /* Sleep for 10 microseconds, then process the wii events */
        usleep(10);
        ProcessWiiEvents();
      
        
    } while (detecting == true);
    
    
    
     SetWiiMoteLights();
     
     WiiMotesInstalled();
     
     wiiuse_rumble(wiimotes[playerWiiIndex], 1);
     usleep(100000);
     wiiuse_rumble(wiimotes[playerWiiIndex], 0);
	


}


void handle_event(struct wiimote_t* wm, int index)
{
    
	if (IS_PRESSED(wm, WIIMOTE_BUTTON_A)) {
	    if (detecting == true)
	    {
	        playerWiiIndex = index;
	        detecting = false;
	        
	    }
	    
	    
	}
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

    fflush(stdout);

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

    
    if(wiimotes[!playerWiiIndex]->ir.dot[0].visible && wiimotes[!playerWiiIndex]->ir.dot[1].visible)
    {
        short dot1x = wiimotes[!playerWiiIndex]->ir.dot[0].rx;
        short dot1y = wiimotes[!playerWiiIndex]->ir.dot[0].ry;
        short dot2x = wiimotes[!playerWiiIndex]->ir.dot[1].rx;
        short dot2y = wiimotes[!playerWiiIndex]->ir.dot[1].ry;

        _camera->ProcessCoordinates(dot1x, dot1y, dot2x, dot2y);

    } else {
        return;
    }


}



void ProcessCursorLocation()
{
    
    if(wiimotes[playerWiiIndex]->ir.dot[0].visible && wiimotes[playerWiiIndex]->ir.dot[1].visible)
        {
            short dot1x = wiimotes[playerWiiIndex]->ir.dot[0].rx;
            short dot1y = wiimotes[playerWiiIndex]->ir.dot[0].ry;
            short dot2x = wiimotes[playerWiiIndex]->ir.dot[1].rx;
            short dot2y = wiimotes[playerWiiIndex]->ir.dot[1].ry;

            _cursor->ProcessCoordinates(dot1x, dot1y, dot2x, dot2y);

        } else {
            return;
        }
    
    
}

void ProcessWiiEvents()
{
    /*
     *  Used to process events from the wii
     */

    //if (numConnectedMotes < 2)
    //    return;

    if (wiiuse_poll(wiimotes, MAX_WIIMOTES))
    {
        int i = 0;
        for (; i< MAX_WIIMOTES; i++)
        {
            switch (wiimotes[i]->event)
            {
            case WIIUSE_EVENT:
                handle_event(wiimotes[i], i);
                break;
            case WIIUSE_READ_DATA:
            case WIIUSE_NONE:
            case WIIUSE_STATUS:
                break;
            case WIIUSE_CONNECT:
                std::cout << "Received connect from " << i;
                break;
            case WIIUSE_DISCONNECT:
                std::cout << "Received disconnect from " << i;
                break;
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
    ProcessCursorLocation();

}



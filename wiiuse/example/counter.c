#include <stdio.h>
#include <stdlib.h>

#ifndef WIN32
	#include <unistd.h>
#endif

#include "wiiuse.h"

#define MAX_WIIMOTES 1

void doSleep(){
	#ifndef WIN32
		usleep(300000);
	#else
		Sleep(300);
	#endif
}

void handle_event(struct wiimote_t* wm) {

}

int main(int argc, char** argv) {
	wiimote** wiimotes;
	int found, connected;

	wiimotes = wiiuse_init(MAX_WIIMOTES);

	found = wiiuse_find(wiimotes, MAX_WIIMOTES, 5);
	if (!found) {
		printf ("No wiimotes found.");
		return 0;
	}

	connected = wiiuse_connect(wiimotes, MAX_WIIMOTES);
	if(connected)
		printf("Connected to wiimote\n");
	else{
		printf("Failed to connect\n");
		return 0;
	}

	while(1){
		wiiuse_set_leds(wiimotes[0], WIIMOTE_LED_1);
		doSleep();
		wiiuse_set_leds(wiimotes[0], WIIMOTE_LED_2);
		doSleep();
		wiiuse_set_leds(wiimotes[0], WIIMOTE_LED_2 | WIIMOTE_LED_1);
		doSleep();
		wiiuse_set_leds(wiimotes[0], WIIMOTE_LED_3);
		doSlep();
		wiiuse_set_leds(wiimotes[0], WIIMOTE_LED_3 | WIIMOTE_LED_1);
		doSleep();
		wiiuse_set_leds(wiimotes[0], WIIMOTE_LED_3 | WIIMOTE_LED_2);
		doSleep();
		wiiuse_set_leds(wiimotes[0], WIIMOTE_LED_3 | WIIMOTE_LED_2 | WIIMOTE_LED_1);
		doSleep();
		wiiuse_set_leds(wiimotes[0], WIIMOTE_LED_4);
		doSlep();
		wiiuse_set_leds(wiimotes[0], WIIMOTE_LED_4 | WIIMOTE_LED_1);
		doSlep();
		wiiuse_set_leds(wiimotes[0], WIIMOTE_LED_4 | WIIMOTE_LED_2);
		doSleep();
		wiiuse_set_leds(wiimotes[0], WIIMOTE_LED_4 | WIIMOTE_LED_2 | WIIMOTE_LED_1);
		doSleep();
		wiiuse_set_leds(wiimotes[0], WIIMOTE_LED_4 | WIIMOTE_LED_3);
		doSleep();
		wiiuse_set_leds(wiimotes[0], WIIMOTE_LED_4 | WIIMOTE_LED_3 | WIIMOTE_LED_1);
		doSleep();
		wiiuse_set_leds(wiimotes[0], WIIMOTE_LED_4 | WIIMOTE_LED_3 | WIIMOTE_LED_2);
		doSleep();
		wiiuse_set_leds(wiimotes[0], WIIMOTE_LED_4 | WIIMOTE_LED_3 | WIIMOTE_LED_2 | WIIMOTE_LED_1);
		doSleep();
		wiiuse_rumble(wiimotes[0], 1);
		doSleep();
		wiiuse_rumble(wiimotes[0], 0);
		doSleep();
	}
	
	wiiuse_cleanup(wiimotes, MAX_WIIMOTES);

	return 0;
}

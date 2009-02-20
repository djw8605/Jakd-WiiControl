

#include <GL/glut.h>
#include "display.h"
#include "events.h"
#include "init.h"
#include "WiiInterface/WiiInterface.h"
#include "config.h"
#include <unistd.h>

int useWiiMotes;


int main(int argc, char *argv[])
{
	useWiiMotes = 1;
	/* Process Arguments */

	int option_char;

	while((option_char = getopt(argc, argv, "n")) != -1)
	{
	    switch (option_char)
	    {
	    case 'n': useWiiMotes = 0; break;

	    }



	}

    /* Connect Wii Motes */
	if(useWiiMotes)
            StartWiiMotes();

	/* Setup Window */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1024, 768);
	glutInitWindowPosition(0,0);
	glutCreateWindow("WiiControl");
	//glutFullScreen();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialKeyboard);
	glutIdleFunc(display);

	/* Intialize everything */
	init();



	/* Enter Game Loop */

	glutMainLoop();

	WiiShutDown();



}




#include <GL/glut.h>
#include "display.h"
#include "events.h"
#include "init.h"
#include "WiiInterface/WiiInterface.h"


int main(int argc, char *argv[])
{
	
	/* Process Arguments */
	
    
    /* Connect Wii Motes */
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
	
	
	
}


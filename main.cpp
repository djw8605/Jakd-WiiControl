

#include <GL/glut.h>
#include "display.h"
#include "events.h"
#include "WiiInterface/WiiInterface.h"


int main(int argc, char *argv[])
{
	
	/* Process Arguments */
	
	
	/* Setup Window */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(winx, winy);
	glutInitWindowPosition(0,0);
	window = glutCreateWindow("WiiControl");
	glutFullScreen();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutKeyboardfunc(keyboard);
	glutSpecialFunc(specialKeyboard);
	glutIdleFunc(display);
	
	
	
	/* Connect Wii Motes */
	StartWiiMotes();
	
	/* Enter Game Loop */
	
	glutMainLoop();
	
	
	
}


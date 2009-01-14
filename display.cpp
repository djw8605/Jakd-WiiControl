
#include <GL/glut.h>
#include "Camera/Camera.h"
#include "WiiInterface/WiiInterface.h"



void display()
{
	
    /* Process Events from wiimotes */
    ProcessWiiEvents();
    
    /* Generic OpenGL stuff */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glPushMatrix();
    
    /* Move Camera */
    camera->positionCamera();
	
    /* List everything to display to the screen here */
	
	
	
	
}


#include "init.h"
#include "display.h"
#include <ctime>
#include <cstdlib>


void init()
{
    
    glEnable(GL_DEPTH_TEST);
    srand(time(0));
    InitDisplay();
    
 
	
	
}



#include "init.h"
#include "display.h"
#include <ctime>
#include <cstdlib>
#include "TextPrinter/BitMapText.h"


void init()
{
    
    glEnable(GL_DEPTH_TEST);
    srand(time(0));
    InitDisplay();
    
    BuildFont();
	
	
}


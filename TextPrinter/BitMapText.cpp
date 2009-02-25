
#include "TextPrinter/BitMapText.h"
#include <GL/glut.h>    // Header File For The GLUT Library 
#include <GL/gl.h>      // Header File For The OpenGL32 Library
#include <GL/glu.h>     // Header File For The GLu32 Library
#include <GL/glx.h>     // Header file fot the glx libraries.
#include <unistd.h>     // Header file for sleeping.
#include <math.h>       // Header file for sin/cos functions.
#include <stdio.h>      // Header file for printf debugging.
#include <string.h>


GLuint base;

void BuildFont(void)
{
    Display *dpy;
    XFontStruct *fontInfo;  // storage for our font.

    base = glGenLists(96);                      // storage for 96 characters.

    // load the font.  what fonts any of you have is going
    // to be system dependent, but on my system they are
    // in /usr/X11R6/lib/X11/fonts/*, with fonts.alias and
    // fonts.dir explaining what fonts the .pcf.gz files
    // are.  in any case, one of these 2 fonts should be
    // on your system...or you won't see any text.

    // get the current display.  This opens a second
    // connection to the display in the DISPLAY environment
    // value, and will be around only long enough to load 
    // the font. 
    dpy = XOpenDisplay(NULL); // default to DISPLAY env.   

    fontInfo = XLoadQueryFont(dpy, "-adobe-helvetica-medium-r-normal--18-*-*-*-p-*-iso8859-1");
    if (fontInfo == NULL) {
        fontInfo = XLoadQueryFont(dpy, "fixed");
        if (fontInfo == NULL) {
            printf("no X font available?\n");
        }
    }

    // after loading this font info, this would probably be the time
    // to rotate, scale, or otherwise twink your fonts.  

    // start at character 32 (space), get 96 characters (a few characters past z), and
    // store them starting at base.
    glXUseXFont(fontInfo->fid, 32, 96, base);

    // free that font's info now that we've got the 
    // display lists.
    XFreeFont(dpy, fontInfo);

    // close down the 2nd display connection.
    XCloseDisplay(dpy);
}

void KillFont(void)                         // delete the font.
{
    glDeleteLists(base, 96);                    // delete all 96 characters.
}



void glPrint(char *text)                      // custom gl print routine.
{
    if (text == NULL) {                         // if there's no text, do nothing.
        return;
    }

    glPushAttrib(GL_LIST_BIT);                  // alert that we're about to offset the display lists with glListBase
    glListBase(base - 32);                      // sets the base character to 32.

    glCallLists(strlen(text), GL_UNSIGNED_BYTE, text); // draws the display list text.
    glPopAttrib();                              // undoes the glPushAttrib(GL_LIST_BIT);
}



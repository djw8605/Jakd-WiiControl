#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "AbstractScene/AbstractScene.h"
#include "FreeType/FreeType.h"

/* Get everything setup */
void InitDisplay();

/* Display function */
void display();

/* To add a scene to the stack */
void AddScene(AbstractScene* toAdd);

/* Get the current scene displayed */
AbstractScene* GetDisplayed();

/* Next Scene */
void NextScene();

/* Previous Scene */
void PrevScene();

/* Get font to print to screen */
freetype::font_data* GetFont();

/* Get the time difference from last render */
double getTime();

/* To shut everything down */
void ShutDown();


#endif /*DISPLAY_H_*/

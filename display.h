#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "AbstractScene/AbstractScene.h"

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





#endif /*DISPLAY_H_*/

#include <GL/glut.h>
#include <sys/time.h>
#include <unistd.h>
#include <iostream>

#include "display.h"
#include "Camera/Camera.h"
#include "WiiInterface/WiiInterface.h"
#include "AbstractScene/AbstractScene.h"
#include "MainMenu/MainMenu.h"
#include "FreeType/FreeType.h"
#include "CastleGame/CastleGame.h"

struct SceneNode {
    AbstractScene* scene;
    SceneNode* next;
};

SceneNode* scenes = NULL;
SceneNode* currentScene = NULL;

/* Definition of function below */
void updateTime();

void InitDisplay()
{
    updateTime();
    
    
    /* Add all of the scenes here */
    AddScene(new CastleGame());
    
    /* Internal Intializers */
    currentScene = scenes;
    currentScene->scene->Init();
    
    
}


void displayScene()
{
    
    currentScene->scene->Render();
    
}


void display()
{
    
    /* Update the time for movement, and the like */
    updateTime();
	
    /* Process Events from wiimotes */
    ProcessWiiEvents();
    
    /* Generic OpenGL stuff */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glPushMatrix();
   
     /* Move Camera */
    /*camera->positionCamera(); */
    
	
    /* List everything to display to the screen here */
    displayScene();
	

    /* And now the normal OpenGL Cleanup stuff */
    glPopMatrix();
    glutSwapBuffers();
    
    usleep(100);
    
}


void AddScene(AbstractScene* toAdd)
{
    /* Add a scene to the list */
    SceneNode* tmpNode = scenes;
    if (tmpNode == NULL)
    {
        scenes = new SceneNode;
        scenes->scene = toAdd;
        scenes->next = NULL;

    }
    else
    {
        while (tmpNode != NULL)
        {
            tmpNode = tmpNode->next;
        }
        tmpNode->next = new SceneNode;
        tmpNode->next->scene = toAdd;
        tmpNode->next->next = NULL;
    }
    
    
    
    
}


AbstractScene* GetDisplayed() 
{
    return currentScene->scene;
    
    
}

freetype::font_data* GetFont()
{
    static freetype::font_data* font = NULL;
    
    if (font == NULL)
    {
        try
        {
            font = new freetype::font_data;
            font->init("FreeType/Test.ttf", 16);
        }
        catch (std::exception &e)
        {
            printf ("%s\n", e.what());
        }

    }
    
    return font;
    
    
    
}

double storeTime = 0, lastTime = 0;
double getTime() {
    return storeTime - lastTime;
}

void updateTime() {
    
    lastTime = storeTime;
    timeval t;
    gettimeofday(&t, 0);
    //store seconds since epoch
    storeTime = t.tv_sec;
    //store micoseconds of that second, so divide by million
    storeTime += ((double)t.tv_usec / 1000000);
    
}




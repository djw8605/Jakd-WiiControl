
#include <GL/glut.h>
#include "Camera/Camera.h"
#include "WiiInterface/WiiInterface.h"
#include "AbstractScene/AbstractScene.h"

struct SceneNode {
    AbstractScene* scene;
    SceneNode* next;
};

SceneNode* scenes = NULL;
SceneNode* currentScene = NULL;

void InitDisplay()
{
    /* Add all of the scenes here */
    
    
    /* Internal Intializers */
    currentScene = scenes;
    
    
}


void displayScene()
{
    
    currentScene->scene->Render();
    
}


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
    displayScene();
	

    /* And now the normal OpenGL Cleanup stuff */
    glPopMatrix();
    glutSwapBuffers();
    
}


void AddScene(AbstractScene* toAdd)
{
    /* Add a scene to the list */
    SceneNode* tmpNode = scenes;
    if (tmpNode == NULL)
    {
        tmpNode = new SceneNode;
        tmpNode->scene = toAdd;
        tmpNode->next = NULL;

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


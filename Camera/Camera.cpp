#include "Camera.h"
#include <GL/glut.h>
#include <GL/glu.h>
#include <math.h>
#include <iostream>
#include <math.h>
#include "display.h"

#define PI 3.14159265

Camera::Camera()
{
    eyeX = 0.0;
    eyeY = -30.0;
    eyeZ = 10.0;
    centerX = 0.0; centerY = 0.0; centerZ = 0.0; upX = 0.0; upY = 0.0; upZ = 1.0;
    shakeCounter = 100000.0;
    m_cameraFreeze = false;
}

Camera::~Camera()
{
}



Camera* Camera::GetInstance()
{

	static Camera* cam = new Camera();
	return cam;

}


void Camera::positionCamera()
{

    float tmpEyeX= 0.0;
    if(shakeCounter < 1.5)
    {
        tmpEyeX = (1*sin(shakeCounter*20))/(pow(shakeCounter*20, 1.3))+eyeX;
        shakeCounter += getTime();
    }
    else
        tmpEyeX = eyeX;
    
    gluLookAt(tmpEyeX, eyeY, eyeZ, centerX, centerY, centerZ, 0.0, 0.0, 1.0);

    
    //std::cout << eyeX << ", " << eyeY << ", " << eyeZ << std::endl;
    
    
    


}



void Camera::ProcessCoordinates(short dot1x, short dot1y, short dot2x, short dot2y)
{
    if(m_cameraFreeze)
        return;
    /*
     * Mathy function to translate the points on a 2d plane to a 3d area
     *
     */

    /* Get the differences */
    float dx = dot1x - dot2x;
    float dy = dot1y - dot2y;

    /* Find the distance between the dots */
    float pointDist = sqrt(dx*dx+dy*dy);

    /* How man radians per pixel.
     * This is a constant that can be changed.  By increasing, you are saying that the camera
     * has a wider field of view, and a very little change in the ir will be reflected more heavily
     */
    float radiansPerPixel = (PI/4)/1024.0f;

    /*
     * This is the angle that the led's are apart.
     */
    float angle = radiansPerPixel * pointDist / 2;

    /*
     * Various constants
     */
    float dotDistanceInMM = 15.0;
    float screenHeightInMM = 25.0;
    float movementScaling = 2.0;

    /*
     * remember, eyeY = forward and backward
     * tan(theta) = opposite/adjacent = (dotDistanceInMM/2) / Distance, solve for Distance
     * Also, the larger the screenHeight, the slower you want to get further away from it
     */
    eyeY = movementScaling * (float)((dotDistanceInMM/2)/tan(angle))/screenHeightInMM;

    /*
     * Get some average values to solve for the correct X (left-right) and Z (up-down) values
     */
    float avgX = (dot1x+dot2x) / 2.0f;
    float avgY = (dot1y + dot2y) / 2.0f;

    /*
     * sin(theta) = opposite/adjacent, solve for opposite (eyeX)
     */
    eyeX = movementScaling * sin(radiansPerPixel * (avgX - 512)) * eyeY;

    /*
     * Angle above the midpoint the user is
     */
    float relativeVerticalAngle = (avgY - 384) * radiansPerPixel;

    /*
     * Initial camera angle (angle that the camera is mounted)
     */
    float cameraVerticalAngle = 0;
    
    /*
     * Nearly the same thing as eyeX, but take in account the mounted angle of the wiimote
     */
    eyeZ = .5f + (float)(movementScaling * sin(relativeVerticalAngle + cameraVerticalAngle) * eyeY);
    
    eyeZ += confCenterZ;

    //eyeY += centerY;
    
    eyeY *= -1.0;
    eyeY += confCenterY;
    
    //eyeY *= -1;

    //eyeX += centerX;
    eyeX += confCenterX;





}

void Camera::SetCameraLocation(float X, float Y, float Z, float newCenterX, float newCenterY, float newCenterZ)
{
    
    confCenterX = X;
    confCenterY = Y;
    confCenterZ = Z;
    centerX = newCenterX;
    centerY = newCenterY;
    centerZ = newCenterZ;
    
    
}

void Camera::ShakeCamera(float intensity)
{
    
    if (intensity <= 0.0)
        return;
    
    
    shakeCounter = 0.0;
    
    
}


void Camera::GetPosition(float* buf)
{
    
    buf[0] = eyeX;
    buf[1] = eyeY;
    buf[2] = eyeZ;
    
    return;
    
}


void Camera::FreezeCamera()
{
    m_cameraFreeze = true;
}

void Camera::UnFreezeCamera()
{
    m_cameraFreeze = false;
}




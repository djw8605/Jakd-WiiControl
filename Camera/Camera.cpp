#include "Camera.h"

Camera::Camera()
{
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
	
	
	
}


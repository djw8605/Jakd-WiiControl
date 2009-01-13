#include "Camera.h"

Camera::Camera()
{
}

Camera::~Camera()
{
}



static Camera* Camera::GetInstance()
{
	
	static Camera* cam = new Camera();
	return cam;
	
}


void Camera::positionCamera()
{
	
	
	
}


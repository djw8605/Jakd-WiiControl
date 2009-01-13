#ifndef CAMERA_H_
#define CAMERA_H_

#define camera Camera::GetInstance()

class Camera
{
public:
	Camera();
	virtual ~Camera();
	
	
	static Camera* GetInstance();			/* Returns the instance of the camera, should be only 1 */
	
	void positionCamera();
	
	void ProcessCoordinates(short dot1x, short dot1y, short dot2x, short dot2y);
};

#endif /*CAMERA_H_*/

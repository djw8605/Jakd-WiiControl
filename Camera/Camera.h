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
	
};

#endif /*CAMERA_H_*/

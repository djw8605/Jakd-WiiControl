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

private:
	float eyeX, eyeY, eyeZ;
	float centerX, centerY, centerZ;
	float upX, upY, upZ;
};

#endif /*CAMERA_H_*/

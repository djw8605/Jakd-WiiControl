
#include "Math/Math.h"


vector Normal(point p1, point p2, point p3)
{
	return Normal(p1.x, p1.y, p1.z, p2.x, p2.y, p2.z, p3.x, p3.y, p3.z);



}

vector Normal(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3)
{



}


bool Intersect(ray r, point v1, point v2, point v3, point v4)
{
/*
A = y1(z2-z3) + y2(z3-z1) + y3(z1-z2)
B = z1(x2-x3) + z2(x3-x1) + z3(x1-x2)
C = x1(y2-y3) + x2(y3-y1) + x3(y1-y2)
D = -x1(y2*z3 - y3*z2) - x2(y3*z1 - y1*z3) - x3(y1*z2 - y2*z1)
 */

	float A =v1.y*(v2.z-v3.z) + v2.y*(v3.z - v1.z) + v3.y*(v1.z - v2.z);

}

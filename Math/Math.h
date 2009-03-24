
#ifndef _VECTOR_H
#define _VECTOR_H

struct point {
	float x, y, z;
};

typedef point vector;

struct ray {
	point origin;
	point direction;
};




vector Normal(point, point, point);
vector Normal(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3);






#endif



#ifndef _DEREKMATH_H
#define _DEREKMATH_H

struct point {
	float x, y, z;
};

typedef point vector;

struct ray {
	point origin;
	point direction;
};

#define dot(v1,v2) v1.x*v2.x+v1.y*v2.y+v1.z*v2.z


vector Normal(point, point, point);
vector Normal(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3);

float Intersect(const ray &r, const point &v1, const point &v2, const point &v3, const point &v4);




#endif


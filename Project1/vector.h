#pragma once

#include <cmath>
#include "image.h"

class vector3
{
protected:
public:
	double x, y, z;
	double length;
	vector3() {}
	vector3(double x, double y, double z);
	vector3 operator +(vector3 other);
	vector3 operator -(vector3 other);
	vector3 operator *(double power);
	vector3* norm();
	vector3 cross(vector3 other);
	double dot(vector3 other) { return other.x* x + other.y * y + other.z * z; }
	double getLength() { return length; };
	~vector3();
	friend class OCTree;
};



class sphere {
	vector3 c;
	double r;
	PIXELDATA colour;
public:
	vector3 getCenter() { return c; }
	double getRadius() { return r; }
	sphere(vector3* C, double R) { c = *C; this->r = R; }
	PIXELDATA getColour() { return colour; }
};

class triangle {
	vector3 a, b, c;
	PIXELDATA colour;
public:
	triangle(vector3* a, vector3* b, vector3* c);
	vector3 getA() { return a; }
	vector3 getB() { return b; }
	vector3 getC() { return c; }
	PIXELDATA getColour() { return colour; }

};


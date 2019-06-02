#pragma once

#include <cmath>

class vector3
{
protected:
	double x, y, z;
	double length;
public:
	vector3() {}
	vector3(double x, double y, double z);
	vector3 operator +(vector3 other);
	vector3 operator -(vector3 other);
	vector3 norm();
	double dot(vector3 other) { return other.x * x + other.y * y + other.z * z; }
	double getLength() { return length; };
	~vector3();
};

class triangle {
	vector3 a, b, c;
	triangle(vector3 a, vector3 b, vector3 c) { this->a = a; this->b = b; this->c = c; }
};


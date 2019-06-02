#include "vector.h"



vector3::vector3(double x, double y, double z) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->length = sqrt(x * x + y * y + z * z);
}

vector3 vector3::operator+(vector3 other) {
	vector3 temp(this->x + other.x, this->y + other.y, this->z + other.z);
	return temp;
}

vector3 vector3::operator-(vector3 other) {
	vector3 temp(this->x - other.x, this->y - other.y, this->z - other.z);
	return temp;
}

vector3 vector3::norm() {
	vector3 temp(x / length, y / length, z / length);
	return temp;
}

vector3::~vector3()
{
}

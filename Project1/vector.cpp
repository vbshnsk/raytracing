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

vector3 vector3::operator*(double power) {
	vector3 result;
	result.x = this->x*power;
	result.y = this->y * power;
	result.z = this->z * power;
	return result;
}

vector3 vector3::operator-(vector3 other) {
	vector3 temp(this->x - other.x, this->y - other.y, this->z - other.z);
	return temp;
}

vector3* vector3::norm() {
	return new vector3(x / length, y / length, z / length);
}

vector3 vector3::cross(vector3 other) {
	vector3 result(
		this->y * other.z - this->z * other.y,
		this->z * other.x - this->x * other.z,
		this->x * other.y - this->y * other.x);
	return result;
}

vector3::~vector3()
{
}

triangle::triangle(vector3* a, vector3* b, vector3* c) {
	this->a = *a;
	this->b = *b;
	this->c = *c;  
	this->colour.blueComponent = 0; 
	this->colour.greenComponent = 0; 
	this->colour.redComponent = 0;
}

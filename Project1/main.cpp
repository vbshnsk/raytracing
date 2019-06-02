#include "vector.h"
#include <conio.h>
#include <cmath>
#include <iostream>

#define PI 3.14

using namespace std;


bool intersect(double r, vector3 sphereC, vector3 camera, vector3 ray) {
	double a, b, c;
	a = ray.dot(ray);
	b = 2 * ray.dot(camera - sphereC);
	c = (camera - sphereC).dot(camera - sphereC) - r * r;
	double D = b * b - 4 * a * c;
	if (D < 0) return false;
	return true;
}

int main() {
	/*vector3 first(0, 1, 3);
	vector3 second(3, 1, 2);
	vector3 third(0, 0, 1);
	triangle myT(first, second, third);*/

	vector3 camera(0, 0, -1),
		direction(0, 0, 1);
	vector3 plane = camera + direction.norm();

	int size = 51;

	bool** canvas = new bool* [size];
	for (int i = 0; i < size; i++) {
		canvas[i] = new bool[size];
	}

	double r = 1;
	vector3 center(0, 0, 2);


	for (int x = 0; x < size; x++) {
		for (int y = 0; y < size; y++) {
			double xNorm = (x - size/2) / (double)size,
				yNorm = - (y - size/2) / (double)size;
			double cameraPlane = (camera - plane).getLength();
			double fov = PI / 3;
			double realPlaneH = cameraPlane * tan(fov);
			vector3 temp(xNorm * realPlaneH / 2, yNorm * realPlaneH / 2, 0);
			vector3 position = plane + temp;
			vector3 dir = position - camera;
			canvas[y][x] = intersect(r, center, camera, dir);
		}
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (canvas[i][j])
				cout << "X ";
			else
				cout << ". ";
		}
		cout << endl;
	}
	for (size_t i = 0; i < size; i++){
		delete[] canvas[i];
	}
}
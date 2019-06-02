#include "vector.h"
#include <conio.h>

#define _USE_MATH_DEFINES

#include <math.h>
#include <iostream>


using namespace std;


bool doesItIntersectSphere(double r, vector3 sphereC, vector3 camera, vector3 ray) {
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

	vector3 camera(0, 0, 0),
		direction(0, 0, 1);
	vector3 plane = camera + direction.norm();

	double height = 48,
		width = 64;

	bool** canvas = new bool* [height]; //2d canvas of pixels
	for (int i = 0; i < height; i++) {
		canvas[i] = new bool[width];
	}

	double r = 1;
	vector3 center(0, 0, 10); //sphere radius and centre coordinates

	double fov = 30;
	double angle = tan(M_PI * 0.5 * fov / 180.);

	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			double xN = (2 * ((x + 0.5) / width) - 1) * angle * width / height,
				yN = (1 - 2 * ((y + 0.5) / height)) * angle;

			vector3 temp(xN, yN, -1);
			/*vector3 position = plane + temp;
			vector3 dir = position - camera;*/
			 temp = temp.norm();
			canvas[y][x] = doesItIntersectSphere(r, center, camera, temp);
		}
	}



	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (canvas[i][j])
				cout << "*";
			else
				cout << ".";
		}
		cout << endl;
	}
	for (size_t i = 0; i < height; i++) {
		delete[] canvas[i];
	}
}
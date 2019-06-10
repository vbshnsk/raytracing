#include "vector.h"
#include "image.h"
#include "cameraPlane.h"


using namespace std;

int main() {
	double height = 1000,
		width = 1000;
	cameraPlane main(-5, height, width);
	main.setAngle(30);
	triangle T(new vector3(-5, 0, 10), new vector3(5, 0, 10), new vector3(0, 5, 10));
	main.putOnScene(T);
	main.traceRays();
	main.name = "image.bmp";
	main.createFile();
	system("pause");
}
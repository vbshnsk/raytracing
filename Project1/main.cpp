#include "vector.h"
#include "image.h"
#include "cameraPlane.h"
#include "OBJparser.h"


using namespace std;

int main() {
	OBJparser cow("cow.obj");
	double height = 1000,
		width = 1000;
	cameraPlane main(-1, height, width);
	main.setAngle(30);
	main.putOnScene(cow.triangles);
	main.traceRays();
	main.name = "image.bmp";
	main.createFile();
	system("pause");
}
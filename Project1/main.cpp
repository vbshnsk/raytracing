#include "vector.h"
#include "image.h"
#include "cameraPlane.h"
#include "OBJparser.h"
#include "OCTree.h"

using namespace std;

int main() {
	OBJparser cow("cow.obj");
	double height = 150,
		width = 150;
	cameraPlane main(0, 1, 0, height, width);
	main.setAngle(30);
	main.putOnScene(cow.triangles, cow.max);
	main.traceRays();
	main.name = "image.bmp";
	main.createFile();
	system("pause");
}
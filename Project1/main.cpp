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
	vector3 origin(0, 0, 0);
	vector3 max(cow.max, cow.max, cow.max);
	vector3 min = max * -1;
	cameraPlane main(0, 1, 0, height, width);
	main.setAngle(30);
	main.putOnScene(origin, max, min, cow.triangles);
	main.traceRays();
	main.name = "image.bmp";
	main.createFile();
	system("pause");
}
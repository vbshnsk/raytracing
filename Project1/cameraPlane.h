#pragma once
#include "vector.h"
#include "image.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>

class cameraPlane :
	public Image
{
private:
	double angle;
	std::vector<triangle*> trianglesOnScene;
	std::vector<sphere*> spheresOnScene;

	bool rayIntersectsTriangle(triangle* T, vector3& pointOfIntersection);
	bool rayIntersectsSphere(sphere* S, vector3& pointOfIntersection);
	void setPixel(int row, int col, PIXELDATA colour);

public:
	vector3* camera;
	vector3* currentRay;

	void traceRays();
	void setAngle(double fov);
	void putOnScene(triangle T);
	void putOnScene(sphere S);

	cameraPlane(double z, int height, int width);
	~cameraPlane();
};


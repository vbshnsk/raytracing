#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>
#include "OCTree.h"

class cameraPlane : public Image
{
private:
	double angle;
	std::vector<sphere*> spheresOnScene;

	bool rayIntersectsTriangle(triangle* T, vector3& pointOfIntersection);
	bool rayIntersectsSphere(sphere* S, vector3& pointOfIntersection);
	void setPixel(int row, int col, PIXELDATA colour);

public:
	OCTree objects;
	vector3* camera;
	vector3* currentRay;

	void traceRays();
	void setAngle(double fov);
	//void putOnScene(triangle T);
	void putOnScene(std::vector<triangle*> Ts, double max) { objects = OCTree(max, Ts); };
	void putOnScene(sphere S);

	cameraPlane(double x, double y, double z, int height, int width);
	~cameraPlane();
};


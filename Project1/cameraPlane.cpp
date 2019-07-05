#include "cameraPlane.h"



cameraPlane::cameraPlane(double x, double y, double z, int canvasH, int canvasW)
{
	this->camera = new vector3(x, y, z);
	this->setHeader(canvasH, canvasW);
	this->setPixels(canvasH, canvasW);
}

void cameraPlane::putOnScene(vector3 center, vector3 max, vector3 min, std::vector<triangle*> triangles)  {
	objects = OCTree(center, max, min);
	objects.insert(triangles);
}

bool cameraPlane::rayIntersectsTriangle(triangle* T, vector3& pointOfIntersection) {
	const double EPS = 0.0000001;
	vector3 vertex0 = T->getA();
	vector3 vertex1 = T->getB();
	vector3 vertex2 = T->getC();
	vector3 edge1 = vertex1 - vertex0;
	vector3 edge2 = vertex2 - vertex0;
	vector3 h = currentRay->cross(edge2);
	double a = edge1.dot(h);
	if (a > -EPS && a < EPS)
		return false;
	double f = 1.0 / a;
	vector3 s = *camera - vertex0;
	double u = f * s.dot(h);
	if (u < 0.0 || u > 1.0)
		return false;
	vector3 q = s.cross(edge1);
	double v = f * currentRay->dot(q);
	if (v < 0.0 || u + v > 1.0)
		return false;
	double t = f * edge2.dot(q);
	if (t > EPS) {
		pointOfIntersection = *camera + *currentRay * t;
		return true;
	}
	else {
		return false;
	}
}

bool cameraPlane::rayIntersectsSphere(sphere* S, vector3& pointOfIntersection) {
	double a, b, c;
	a = currentRay->dot(*currentRay);
	b = 2 * currentRay->dot(*camera - S->getCenter());
	c = (*camera - S->getCenter()).dot(*camera - S->getCenter()) - S->getRadius() * S->getRadius();
	double D = b * b - 4 * a * c;
	if (D < 0) return false;
	if (D > 0) {
		double x1 = (-b + sqrt(D)) / (2 * a),
			x2 = (-b - sqrt(D)) / (2 * a);
		if (x1 < 0 && x2 < 0)
			return false;
	}
	return true;
}

void cameraPlane::setPixel(int row, int col, PIXELDATA colour) {
	this->pixels[row][col] = colour;
}

void cameraPlane::setAngle(double fov) {
	angle = tan(M_PI * fov / 180.);
}

void cameraPlane::traceRays() {
	vector3 t;
	for (int y = 0; y < this->header.depth; y++) {
		for (int x = 0; x < this->header.width; x++) {
			double xD = (2 * ((x + 0.5) / this->header.width) - 1) * angle * this->header.width / this->header.depth,
				yD = (2 * ((y + 0.5) / this->header.depth) - 1) * angle;
			currentRay = new vector3(xD, -1, yD);
			currentRay = currentRay->norm();
			std::vector<triangle*> validTriangles;
			objects.checkIntersection(*currentRay, *camera, validTriangles);
			for (auto triangle : validTriangles)
				if (rayIntersectsTriangle(triangle, t))
					pixels[y][x] = triangle->getColour();
			/*for (auto triangle : trianglesOnScene)
				if (rayIntersectsTriangle(triangle, t))
					pixels[y][x] = triangle->getColour();
			for (auto sphere : spheresOnScene)
				if (rayIntersectsSphere(sphere, t))
					pixels[x][y] = sphere->getColour();*/
		}
	}
}

//void cameraPlane::putOnScene(triangle T) {
//	trianglesOnScene.push_back(new triangle(T));
//}

void cameraPlane::putOnScene(sphere S) {
	spheresOnScene.push_back(new sphere(S));
}

cameraPlane::~cameraPlane()
{
}

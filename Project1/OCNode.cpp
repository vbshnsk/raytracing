#include "OCNode.h"



OCNode::OCNode(std::vector<double> X, std::vector<double> Y, std::vector<double> Z)
{
	vector3 A(X[0], Y[0], Z[0]);
	vector3 B(X[0], Y[1], Z[0]);
	vector3 C(X[1], Y[1], Z[0]);
	vector3 D(X[1], Y[0], Z[0]);
	vector3 E(X[0], Y[0], Z[1]);
	vector3 F(X[0], Y[1], Z[1]);
	vector3 G(X[1], Y[1], Z[1]);
	vector3 H(X[1], Y[0], Z[1]);

	this->space = Cube(A, B, C, D, E, F, G, H);

}


Cube::Cube(vector3 A, vector3 B, vector3 C, vector3 D, vector3 E, vector3 F, vector3 G, vector3 H) {
	this->vertices.push_back(A);
	this->vertices.push_back(B);
	this->vertices.push_back(C);
	this->vertices.push_back(D);
	this->vertices.push_back(E);
	this->vertices.push_back(F);
	this->vertices.push_back(G);
	this->vertices.push_back(H);

	faces.push_back(triangle(&A, &B, &C));
	faces.push_back(triangle(&A, &D, &C));

	faces.push_back(triangle(&A, &B, &E));
	faces.push_back(triangle(&E, &B, &F));

	faces.push_back(triangle(&A, &D, &E));
	faces.push_back(triangle(&E, &D, &H));

	faces.push_back(triangle(&D, &C, &H));
	faces.push_back(triangle(&H, &C, &G));

	faces.push_back(triangle(&B, &C, &F));
	faces.push_back(triangle(&F, &C, &G));

	faces.push_back(triangle(&E, &F, &G));
	faces.push_back(triangle(&E, &G, &H));
}

void OCNode::rebuild(double min) {
	std::vector<double> newX;
	std::vector<double> newY;
	std::vector<double> newZ;

	vector3 C = (space.vertices[0] + space.vertices[6]) * 0.5;

	if (trianglesInCube.size() < 10)
		return;

	newX.push_back(space.vertices[0].x);
	newX.push_back((space.vertices[0].x + space.vertices[3].x) * 0.5);
	newY.push_back(space.vertices[0].y);
	newY.push_back((space.vertices[0].y + space.vertices[1].y) * 0.5);
	newZ.push_back(space.vertices[0].z);
	newZ.push_back((space.vertices[0].z + space.vertices[4].z) * 0.5);

	if ((newX[1] - newX[0]) < min)
		return;

	children.push_back(new OCNode(newX, newY, newZ));

	newX.clear();
	newY.clear();
	newZ.clear();

	newX.push_back(space.vertices[0].x);
	newX.push_back((space.vertices[0].x + space.vertices[3].x) * 0.5);
	newY.push_back((space.vertices[0].y + space.vertices[1].y) * 0.5);
	newY.push_back(space.vertices[1].y);
	newZ.push_back(space.vertices[0].z);
	newZ.push_back((space.vertices[0].z + space.vertices[4].z) * 0.5);

	children.push_back(new OCNode(newX, newY, newZ));

	newX.clear();
	newY.clear();
	newZ.clear();

	newX.push_back((space.vertices[0].x + space.vertices[3].x) * 0.5);
	newX.push_back(space.vertices[3].x);
	newY.push_back((space.vertices[0].y + space.vertices[1].y) * 0.5);
	newY.push_back(space.vertices[1].y);
	newZ.push_back(space.vertices[0].z);
	newZ.push_back((space.vertices[0].z + space.vertices[4].z) * 0.5);

	children.push_back(new OCNode(newX, newY, newZ));

	newX.clear();
	newY.clear();
	newZ.clear();

	newX.push_back((space.vertices[0].x + space.vertices[3].x) * 0.5);
	newX.push_back(space.vertices[3].x);
	newY.push_back(space.vertices[0].y);
	newY.push_back((space.vertices[0].y + space.vertices[1].y) * 0.5);
	newZ.push_back(space.vertices[0].z);
	newZ.push_back((space.vertices[0].z + space.vertices[4].z) * 0.5);

	children.push_back(new OCNode(newX, newY, newZ));

	newX.clear();
	newY.clear();
	newZ.clear();

	newX.push_back(space.vertices[0].x);
	newX.push_back((space.vertices[0].x + space.vertices[3].x) * 0.5);
	newY.push_back(space.vertices[0].y);
	newY.push_back((space.vertices[0].y + space.vertices[1].y) * 0.5);
	newZ.push_back((space.vertices[0].z + space.vertices[4].z) * 0.5);
	newZ.push_back(space.vertices[4].z);

	children.push_back(new OCNode(newX, newY, newZ));

	newX.clear();
	newY.clear();
	newZ.clear();

	newX.push_back(space.vertices[0].x);
	newX.push_back((space.vertices[0].x + space.vertices[3].x) * 0.5);
	newY.push_back((space.vertices[0].y + space.vertices[1].y) * 0.5);
	newY.push_back(space.vertices[1].y);
	newZ.push_back((space.vertices[0].z + space.vertices[4].z) * 0.5);
	newZ.push_back(space.vertices[4].z);

	children.push_back(new OCNode(newX, newY, newZ));

	newX.clear();
	newY.clear();
	newZ.clear();

	newX.push_back((space.vertices[0].x + space.vertices[3].x) * 0.5);
	newX.push_back(space.vertices[3].x);
	newY.push_back((space.vertices[0].y + space.vertices[1].y) * 0.5);
	newY.push_back(space.vertices[1].y);
	newZ.push_back((space.vertices[0].z + space.vertices[4].z) * 0.5);
	newZ.push_back(space.vertices[4].z);

	children.push_back(new OCNode(newX, newY, newZ));

	newX.clear();
	newY.clear();
	newZ.clear();

	newX.push_back((space.vertices[0].x + space.vertices[3].x) * 0.5);
	newX.push_back(space.vertices[3].x);
	newY.push_back(space.vertices[0].y);
	newY.push_back((space.vertices[0].y + space.vertices[1].y) * 0.5);
	newZ.push_back((space.vertices[0].z + space.vertices[4].z) * 0.5);
	newZ.push_back(space.vertices[4].z);

	children.push_back(new OCNode(newX, newY, newZ));

	newX.clear();
	newY.clear();
	newZ.clear();

	std::vector<triangle*> leftovers;

	while (!trianglesInCube.empty()) {
		int octantA = -1;
		int octantB = -1;
		int octantC = -1;

		triangle* current = trianglesInCube.back();
		trianglesInCube.pop_back();

		octantA = checkForOctant(current->getA(), C);
		octantB = checkForOctant(current->getB(), C);
		octantC = checkForOctant(current->getC(), C);

		if (octantA == octantB && octantB == octantC)
			children[octantA]->trianglesInCube.push_back(current);
		else
			leftovers.push_back(current);
	}
	trianglesInCube = leftovers;

	for (auto child : children) {
		child->rebuild(min);
	}

}

int OCNode::checkForOctant(vector3 point, vector3 center) {
	if (point.x > center.x)
		if (point.y > center.y)
			if (point.z > center.z)
				return 6;
			else
				return 2;
		else
			if (point.z > center.z)
				return 7;
			else
				return 3;
	else
		if (point.y > center.y)
			if (point.z > center.z)
				return 5;
			else
				return 1;
		else
			if (point.z > center.z)
				return 4;
			else
				return 0;
}


void OCNode::checkPossibleIntersections(vector3 camera, vector3 ray, std::vector<triangle>& trianglesThatIntersect) {
	for (auto T : trianglesInCube) {
		trianglesThatIntersect.push_back(*T);
	}
	if (children.empty())
		return;

	for (auto child : children)
		if (child && child->space.intersectionCube(camera, ray))
			child->checkPossibleIntersections(camera, ray, trianglesThatIntersect);
}



bool Cube::intersectionCube(vector3 camera, vector3 ray) {
	for (auto T : faces)
		if (intersectionTriangle(camera, ray, T))
			return true;
	return false;
}

bool Cube::intersectionTriangle(vector3 camera, vector3 ray, triangle T) {
	const double EPS = 0.0000001;
	vector3 vertex0 = T.getA();
	vector3 vertex1 = T.getB();
	vector3 vertex2 = T.getC();
	vector3 edge1 = vertex1 - vertex0;
	vector3 edge2 = vertex2 - vertex0;
	vector3 h = ray.cross(edge2);
	double a = edge1.dot(h);
	if (a > -EPS && a < EPS)
		return false;
	double f = 1.0 / a;
	vector3 s = camera - vertex0;
	double u = f * s.dot(h);
	if (u < 0.0 || u > 1.0)
		return false;
	vector3 q = s.cross(edge1);
	double v = f * ray.dot(q);
	if (v < 0.0 || u + v > 1.0)
		return false;
	double t = f * edge2.dot(q);
	if (t > EPS) {
		return true;
	}
	else {
		return false;
	}
}

OCNode::~OCNode()
{
}

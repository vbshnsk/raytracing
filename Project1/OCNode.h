#pragma once
#include <vector>
#include "vector.h"


class Cube
{
private:
public:
	std::vector<vector3> vertices;
	std::vector<triangle> faces;
	bool intersectionCube(vector3 camera, vector3 ray);
	bool intersectionTriangle(vector3 camera, vector3 ray, triangle T);
	Cube() {}
	Cube(vector3 A, vector3 B, vector3 C, vector3 D, vector3 E, vector3 F, vector3 G, vector3 H);
};


class OCNode
{
private:
	Cube space;
public:
	std::vector<triangle*> trianglesInCube;
	std::vector<OCNode*> children;
	OCNode(std::vector<double> X, std::vector<double> Y, std::vector<double> Z);
	void rebuild(double min);
	void checkPossibleIntersections(vector3 camera, vector3 ray, std::vector<triangle>& trianglesThatIntersect);
	int checkForOctant(vector3 point, vector3 center);
	~OCNode();
};
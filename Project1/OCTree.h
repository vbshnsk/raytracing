#pragma once
#include <vector>
#include "vector.h"

class OCTree
{
private:
	vector3 max;
	vector3 min;
	vector3 center;
public:
	std::vector<OCTree*> children;
	std::vector<triangle*> trianglesInThisCube;
	OCTree(vector3 origin, vector3 max, vector3 min);
	OCTree() {}
	int checkForOctant(vector3 point);
	bool isLeaf();
	void insert(std::vector<triangle*> triangles);
	bool rayBoxIntersection(vector3 ray, vector3 camera);
	void checkIntersection(vector3 ray, vector3 camera, std::vector<triangle*> &valid);
	~OCTree();
};


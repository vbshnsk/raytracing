#include "OCTree.h"



OCTree::OCTree(vector3 origin, vector3 max, vector3 min)
{
	this->center = origin;
	this->max = max;
	this->min = min;
}

int OCTree::checkForOctant(vector3 point) {
	if (point.x > center.x)
		if (point.y > center.y)
			if (point.z > center.z)
				return 7;
			else
				return 6;
		else
			if (point.z > center.z)
				return 5;
			else
				return 4;
	else
		if (point.y > center.y)
			if (point.z > center.z)
				return 3;
			else
				return 2;
		else
			if (point.z > center.z)
				return 1;
			else
				return 0;
}

void OCTree::insert(std::vector<triangle*> triangles) {
	if (triangles.size() < 100 || max.x < 0.001 || max.y < 0.001 || max.z < 0.001)
		return;
	for (int i = 0; i < 8; i++) {
		vector3 newCenter = center;
		newCenter.x += max.x * (i & 4 ? .5 : -.5);
		newCenter.y += max.y * (i & 2 ? .5 : -.5);
		newCenter.z += max.z * (i & 1 ? .5 : -.5);
		vector3 newMax = newCenter * 2;
		vector3 newMin = center;
		children.push_back(new OCTree(newCenter, newMax, newMin));
	}
	std::vector<triangle*> leftovers;
	while (!triangles.empty()) {
		auto T = triangles.back();
		triangles.pop_back();
		int octantA = checkForOctant(T->getA());
		int octantB = checkForOctant(T->getB());
		int octantC = checkForOctant(T->getC());
		if (octantA == octantB && octantC == octantB)
			children[octantA]->trianglesInThisCube.push_back(T);
		else
			leftovers.push_back(T);
	}
	trianglesInThisCube = leftovers;
	for (auto child : children) {
		child->insert(child->trianglesInThisCube);
	}
}

bool OCTree::rayBoxIntersection(vector3 ray, vector3 camera) {
	double tmin = (min.x - camera.x) / ray.x;
	double tmax = (max.x - camera.x) / ray.x;

	if (tmin > tmax)
		std::swap(tmin, tmax);

	double ymin = (min.y - camera.y) / ray.y;
	double ymax = (max.y - camera.y) / ray.y;

	if (ymin > ymax)
		std::swap(ymin, ymax);

	if ((tmin > ymax) || (ymin > tmax))
		return false;

	if (ymin > tmin)
		tmin = ymin;
	if (ymax < tmax)
		tmax = ymax;

	double zmin = (min.z - camera.z) / ray.z;
	double zmax = (max.z - camera.z) / ray.z;

	if (zmin > zmax)
		std::swap(zmin, zmax);

	if ((tmin > zmax) || (zmin > tmax))
		return false;

	return true;

}

void OCTree::checkIntersection(vector3 ray, vector3 camera, std::vector<triangle*> & valid) {
	if (rayBoxIntersection(ray, camera)) {
		valid.insert(valid.end(), trianglesInThisCube.begin(), trianglesInThisCube.end());
		for (auto child : children) {
			child->checkIntersection(ray, camera, valid);
		}
	}
}

bool OCTree::isLeaf() {
	return children.empty();
}

OCTree::~OCTree()
{
}

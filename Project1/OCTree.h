#pragma once
#include <vector>
#include "OCNode.h"

class OCTree
{
private:
	double min;
	double max;
public:
	OCNode* top;
	OCTree() {}
	OCTree(double max, std::vector<triangle*> trianglesOnScene);
	~OCTree();
};


#include "OCTree.h"



OCTree::OCTree(double max, std::vector<triangle*> trianglesOnScene)
{
	this->min = max / 10;
	this->max = max;
	top = new OCNode({ -max, max }, { -max, max }, { -max, max });
	top->trianglesInCube = trianglesOnScene;
	top->rebuild(min);
}


OCTree::~OCTree()
{
}

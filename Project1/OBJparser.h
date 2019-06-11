#pragma once
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "vector.h"


class OBJparser
{
private:
	std::vector<vector3*> vertices;
	std::vector<vector3*> normals;
public:
	std::vector<triangle*> triangles;
	OBJparser(const char* name);
	~OBJparser();
};


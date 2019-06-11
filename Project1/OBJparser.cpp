#include "OBJparser.h"



OBJparser::OBJparser(const char* name)
{
	std::ifstream file(name);
	std::string currentLine;
	std::vector<vector3*> unsortedN;
	while (std::getline(file, currentLine)) {
		if (currentLine.substr(0, 2) == "v ") {
			std::istringstream vert(currentLine.substr(2));
			double x, y, z;
			vert >> x;
			vert >> y;
			vert >> z;
			vertices.push_back(new vector3(x, y, z));
		}
		if (currentLine.substr(0, 2) == "vn") {
			std::istringstream norm(currentLine.substr(2));
			double x, y, z;
			norm >> x;
			norm >> y;
			norm >> z;
			unsortedN.push_back(new vector3(x, y, z));
		}
		if (currentLine.substr(0, 2) == "f ") {
			std::istringstream vertInfo(currentLine.substr(2));
			std::vector<int> vI;
			while (vertInfo) {
				std::string split;
				vertInfo >> split;
				if (split == "")
					break;
				std::string vStringIndex = split.substr(0, split.find('/'));
				std::string nStringIndex = split.substr(split.find_last_of('/') + 1);
				int vIndex = stoi(vStringIndex) - 1;
				int nIndex = stoi(nStringIndex) - 1;
				vI.push_back(vIndex);
				normals.push_back(unsortedN[nIndex]);
			}
			triangles.push_back(new triangle(vertices[vI[0]], vertices[vI[1]], vertices[vI[2]]));
		}
	}
}


OBJparser::~OBJparser()
{
}

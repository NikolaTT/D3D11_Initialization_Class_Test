#ifndef H_GEOMETRY
#define H_GEOMETRY

#include <string>
#include <vector>
#include "VertexTypes.h"


typedef unsigned short USHORT;

class Object{

public:
	std::string fileName;
	std::string objectName;
	std::string techniqueName;
	std::vector<VertexTypes::VertexBasic> vertices;
	USHORT* indices = nullptr;

	Object(std::string fileName);
};

#endif
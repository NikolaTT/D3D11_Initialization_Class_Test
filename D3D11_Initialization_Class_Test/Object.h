#ifndef H_GEOMETRY
#define H_GEOMETRY

#include <string>
#include <vector>
#include "VertexTypes.h"


typedef unsigned short USHORT;

class Object{

public:
	std::string fileName;
	std::string ObjectName;
	std::vector<VertexTypes::VertexBasic> vertices;
	std::vector<USHORT> indices;

	Object(std::string fileName);
};

#endif
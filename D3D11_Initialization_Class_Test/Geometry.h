#ifndef H_GEOMETRY
#define H_GEOMETRY

#include <string>
#include <vector>
#include "VertexTypes.h"


typedef unsigned short USHORT;

class Geometry{

public:
	std::string fileName;
	std::vector<VertexTypes::VertexBasic> vertices;
	std::vector<USHORT> indices;

	Geometry(std::string fileName);
};

#endif
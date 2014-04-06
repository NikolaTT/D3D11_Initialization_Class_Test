#include <string>
#include <vector>
#include "VertexTypes.h"
#include "ObjModelParser.h"

typedef unsigned short USHORT;

class Geometry{

public:
	std::string fileName;
	std::vector<VertexTypes::VertexBasic> vertices;
	std::vector<USHORT> indices;

	Geometry(std::string fileName);
};
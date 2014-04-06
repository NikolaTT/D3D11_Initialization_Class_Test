#ifndef H_BASIC_LEVEL
#define H_BASIC_LEVEL

#include <string>
#include <vector>
#include "Geometry.h"
#include "GeometryLoader.h"

class BasicLevel{

public:
	std::string levelFileName;
	std::vector<Geometry> levelGeometryVector;

	BasicLevel(){}

	BasicLevel(std::string fileName);

};


#endif
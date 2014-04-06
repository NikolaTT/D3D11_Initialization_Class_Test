#ifndef H_GEOMETRY_LOADER
#define H_GEOMETRY_LOADER

#include "Geometry.h"
#include "ObjModelParser.h"

//fileName includes names of files to load

class GeometryLoader{

public:
	bool LoadGeometry(std::string fileName, std::vector<Geometry>& geometry);
};

#endif
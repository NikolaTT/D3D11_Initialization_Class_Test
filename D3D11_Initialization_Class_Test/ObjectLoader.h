#ifndef H_GEOMETRY_LOADER
#define H_GEOMETRY_LOADER

#include "Object.h"
#include "ObjModelParser.h"

//fileName includes names of files to load

class ObjectLoader{

public:
	bool LoadGeometry(std::string fileName, std::vector<Object>& geometry);
};

#endif
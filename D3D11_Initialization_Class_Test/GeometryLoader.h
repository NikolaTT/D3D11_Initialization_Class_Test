#include "Geometry.h"
#include "ObjModelParser.h"

//fileName includes names of files to load

class GeometryLoader{

public:
	GeometryLoader(std::string fileName, std::vector<Geometry>& geometry);
};
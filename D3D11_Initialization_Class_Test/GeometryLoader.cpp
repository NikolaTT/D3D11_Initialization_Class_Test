#include "GeometryLoader.h"
#include <fstream>


bool GeometryLoader::LoadGeometry(std::string fileName, std::vector<Geometry>& geometry){
	
	bool loaded = false;

	std::ifstream fin(fileName);
	std::string geometryFile;

	ObjModelParser objModelParser;

	while (std::getline(fin, geometryFile)){
		Geometry object(geometryFile);
		objModelParser.LoadObj(object);
		geometry.push_back(object);
		loaded = true;
	}	
	return loaded;
}
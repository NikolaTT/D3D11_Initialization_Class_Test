#include "GeometryLoader.h"
#include <fstream>


GeometryLoader::GeometryLoader(std::string fileName, std::vector<Geometry>& geometry){
	
	std::ifstream fin(fileName);
	std::string geometryFile;

	ObjModelParser objModelParser;

	while (std::getline(fin, geometryFile)){
		Geometry object(geometryFile);
		objModelParser.LoadObj(object);
		geometry.push_back(object);
	}
}
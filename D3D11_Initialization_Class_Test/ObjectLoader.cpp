#include "ObjectLoader.h"
#include <fstream>


bool ObjectLoader::LoadGeometry(std::string fileName, std::vector<Object>& geometry){
	
	bool loaded = false;

	std::ifstream fin(fileName);
	std::string geometryFile;

	ObjModelParser objModelParser;

	while (std::getline(fin, geometryFile)){
		Object object(geometryFile);
		objModelParser.LoadObj(object);
		geometry.push_back(object);
		loaded = true;
	}	
	return loaded;
}
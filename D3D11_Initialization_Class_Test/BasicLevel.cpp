#include "BasicLevel.h"

BasicLevel::BasicLevel(std::string fileName) : levelFileName(fileName){

	ObjectLoader levelGeometryLoader;
	levelGeometryLoader.LoadGeometry(levelFileName, levelGeometryVector);

	for (int i = 0; i < levelGeometryVector.size(); i++){

		for (int j = 0; j < levelGeometryVector[i].vertices.size(); j++){

			vertices.push_back(levelGeometryVector[i].vertices[j]);

		}
	}

}

void BasicLevel::setVertices(){

	for (int i = 0; i < vertices.size(); i++){

		mTDevice->vertices[i] = vertices[i];

	}

}

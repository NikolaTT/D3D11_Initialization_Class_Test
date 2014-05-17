#include "BasicLevel.h"

BasicLevel::BasicLevel(std::string fileName) : levelFileName(fileName){

	ObjectLoader levelGeometryLoader;
	levelGeometryLoader.LoadGeometry(levelFileName, levelGeometryVector);

	for (int i = 0; i < levelGeometryVector.size(); i++){

		for (int j = 0; j < levelGeometryVector[i].vertices.size(); j++){
			vertices.push_back(levelGeometryVector[i].vertices[j]);
		}
		for (int j = 0; j < levelGeometryVector[i].numIndices; j++){
			indices.push_back(levelGeometryVector[i].indices[j]);
		}
	}

}

void BasicLevel::setVertices(){

	for (int i = 0; i < vertices.size(); i++){

		mTDevice->vertices[i] = vertices[i];

	}

}

void BasicLevel::setIndices(){

	for (int i = 0; i < indices.size(); i++){
		mTDevice->indices[i] = indices[i];
	}

}
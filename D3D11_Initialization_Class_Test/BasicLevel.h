#ifndef H_BASIC_LEVEL
#define H_BASIC_LEVEL

#include <string>
#include <vector>
#include "Object.h"
#include "ObjectLoader.h"
#include "D3DInitializer.h"

class BasicLevel{

public:
	D3DInitializer* mTDevice;
	std::string levelFileName;
	std::vector<Object> levelGeometryVector;
	std::vector<VertexTypes::VertexBasic> vertices;
	int numVertices = 0;

	BasicLevel(){}

	BasicLevel(std::string fileName);

	void setInitializer(D3DInitializer* mTDevice){
		this->mTDevice = mTDevice;
	}

	void setVertices();

};


#endif
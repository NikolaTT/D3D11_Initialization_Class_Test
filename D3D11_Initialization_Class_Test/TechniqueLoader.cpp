#include "TechniqueLoader.h"
#include <fstream>
#include "StringManipulator.h"
#include <vector>


TechniqueLoader::TechniqueLoader(std::string filename, std::map < std::string, Technique >& techniqueMap,
	ID3D11Device* g_pd3dDevice, InputLayoutDescription &layouts, std::map<std::string, ID3D11InputLayout*>& g_pVertexLayoutMap){
	loadTechnique(filename, techniqueMap, g_pd3dDevice, layouts, g_pVertexLayoutMap);
}

void TechniqueLoader::loadTechnique(std::string filename, std::map < std::string, Technique >& techniqueMap,
	ID3D11Device* g_pd3dDevice, InputLayoutDescription &layouts, std::map<std::string, ID3D11InputLayout*>& g_pVertexLayoutMap){
	std::ifstream fin(filename);
	
	while (fin){
		Technique currentTech;

		std::string techniqueName;
		std::getline(fin, techniqueName);
		
		if (techniqueName == "")
			break;
		
		techniqueName = techniqueName.substr(12, std::string::npos);

		std::vector<std::string> stringVector;
		std::string line;
		int tokens;
		std::getline(fin, line);
		divideString(line, ' ', stringVector);

		size_t fileNameLength = stringVector[0].length() + 1;
		wchar_t * wFileName = new wchar_t[fileNameLength];
		size_t convertedChars = 0;
		mbstowcs_s(&convertedChars, wFileName, fileNameLength, stringVector[0].c_str(), _TRUNCATE);

		g_pVertexLayoutMap[stringVector[3]] = currentTech.setVertexShader(wFileName, stringVector[1].c_str(), stringVector[2].c_str(),
			g_pd3dDevice, layouts.inputLayoutDescriptionMap[stringVector[3]]);


		//
		//
		//

		stringVector.clear();
		delete[] wFileName;

		std::getline(fin, line);
		divideString(line, ' ', stringVector);

		fileNameLength = stringVector[0].length() + 1;
		wFileName = new wchar_t[fileNameLength];
		convertedChars = 0;
		mbstowcs_s(&convertedChars, wFileName, fileNameLength, stringVector[0].c_str(), _TRUNCATE);

		currentTech.setPixelShader(wFileName, stringVector[1].c_str(), stringVector[2].c_str(),
			g_pd3dDevice);


		//
		//
		//

		stringVector.clear();
		delete[] wFileName;

		std::getline(fin, line);
		divideString(line, ' ', stringVector);

		fileNameLength = stringVector[0].length() + 1;
		wFileName = new wchar_t[fileNameLength];
		convertedChars = 0;
		mbstowcs_s(&convertedChars, wFileName, fileNameLength, stringVector[0].c_str(), _TRUNCATE);

		currentTech.setHullShader(wFileName, stringVector[1].c_str(), stringVector[2].c_str(),
			g_pd3dDevice);

		//
		//
		//

		stringVector.clear();
		delete[] wFileName;

		std::getline(fin, line);
		divideString(line, ' ', stringVector);

		fileNameLength = stringVector[0].length() + 1;
		wFileName = new wchar_t[fileNameLength];
		convertedChars = 0;
		mbstowcs_s(&convertedChars, wFileName, fileNameLength, stringVector[0].c_str(), _TRUNCATE);

		currentTech.setDomainShader(wFileName, stringVector[1].c_str(), stringVector[2].c_str(),
			g_pd3dDevice);

		stringVector.clear();
		delete[] wFileName;

		techniqueMap[techniqueName] = currentTech;
	}
}
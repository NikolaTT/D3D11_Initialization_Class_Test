#ifndef H_TECHNIQUE_LOADER
#define H_TECHNIQUE_LOADER

#include <string>
#include "Technique.h"
#include "InputLayoutDescription.h"
#include <map>

class TechniqueLoader{


public:

	void loadTechnique(std::string filename, std::map < std::string, Technique >& techniqueMap, ID3D11Device* g_pd3dDevice,
		InputLayoutDescription &layouts, std::map<std::string, ID3D11InputLayout*>& g_pVertexLayoutMap);

	TechniqueLoader(std::string filename, std::map < std::string, Technique >& techniqueMap, ID3D11Device* g_pd3dDevice,
		InputLayoutDescription &layouts, std::map<std::string, ID3D11InputLayout*>& g_pVertexLayoutMap);
	TechniqueLoader(){};
};

#endif
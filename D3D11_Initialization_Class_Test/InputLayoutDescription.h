#ifndef H_INPUT_LAYOUT_DESCRIPTION
#define H_INPUT_LAYOUT_DESCRIPTION

#include <d3d11_1.h>
#include <map>
#include <string>

struct ToshLayout{
	D3D11_INPUT_ELEMENT_DESC* mTlayout;
	UINT numElements = 0;
};

class InputLayoutDescription{

public:
	std::map<std::string, ToshLayout> inputLayoutDescriptionMap;
	InputLayoutDescription();
};


#endif
#ifndef H_TECHNIQUE
#define H_TECHNIQUE
#include <d3d11_1.h>
#include <string>
#include "InputLayoutDescription.h"

class Technique{

public:
	ID3D11VertexShader* g_pVertexShader = nullptr;
	ID3D11PixelShader* g_pPixelShader = nullptr;
	ID3D11HullShader* g_pHullShader = nullptr;
	ID3D11DomainShader* g_pDomainShader = nullptr;
	ID3D11ComputeShader* g_pComputeShader = nullptr;
	std::string layoutName;

	Technique(){};

	ID3D11InputLayout* setVertexShader(LPCWSTR filename, LPCSTR entryPoint, LPCSTR shaderModel, ID3D11Device* g_pd3dDevice, ToshLayout mTlayout);
	HRESULT setPixelShader(LPCWSTR filename, LPCSTR entryPoint, LPCSTR shaderModel, ID3D11Device* g_pd3dDevice);
	HRESULT setHullShader(LPCWSTR filename, LPCSTR entryPoint, LPCSTR shaderModel, ID3D11Device* g_pd3dDevice);
	HRESULT setDomainShader(LPCWSTR filename, LPCSTR entryPoint, LPCSTR shaderModel, ID3D11Device* g_pd3dDevice);
	HRESULT setComputeShader(LPCWSTR filename, LPCSTR entryPoint, LPCSTR shaderModel, ID3D11Device* g_pd3dDevice);

	void operator=(const Technique& tech2);
};

#endif
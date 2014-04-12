#include <d3d11_1.h>



class ShaderHandler{
	ID3D11VertexShader* g_pVertexShader;
	ID3D11HullShader* g_pHullShader;
	ID3D11DomainShader* g_pDomainShader;
	ID3D11ComputeShader* g_pComputeShader;
	ID3D11PixelShader* g_pPixelShader;	
};
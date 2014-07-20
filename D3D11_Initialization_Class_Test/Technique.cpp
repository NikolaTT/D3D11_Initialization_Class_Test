#include "Technique.h"
#include "StringManipulator.h"
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <fstream>

ID3D11InputLayout* Technique::setVertexShader(LPCWSTR filename, LPCSTR entryPoint, LPCSTR shaderModel,
	ID3D11Device* g_pd3dDevice, ToshLayout layout){
	HRESULT hr = S_OK;

	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
	// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
	// Setting this flag improves the shader debugging experience, but still allows 
	// the shaders to be optimized and to run exactly the way they will run in 
	// the release configuration of this program.
	dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

	ID3DBlob* pVSBlob = nullptr;
	ID3DBlob* pErrorBlob = nullptr;
	hr = D3DCompileFromFile(filename, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, entryPoint, shaderModel,
		dwShaderFlags, 0, &pVSBlob, &pErrorBlob);
	if (FAILED(hr))
	{
		if (pErrorBlob)
		{
			std::ofstream fout("Shader_Debug.txt");
			fout << reinterpret_cast<const char*>(pErrorBlob->GetBufferPointer());
			OutputDebugStringA(reinterpret_cast<const char*>(pErrorBlob->GetBufferPointer()));
			pErrorBlob->Release();
		}
		
	}
	if (pErrorBlob) pErrorBlob->Release();

	hr = g_pd3dDevice->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, &g_pVertexShader);
	if (FAILED(hr))
	{
		pVSBlob->Release();
		
	}

	ID3D11InputLayout* g_pVertexLayout = nullptr;


	hr = g_pd3dDevice->CreateInputLayout(layout.mTlayout, layout.numElements, pVSBlob->GetBufferPointer(),
		pVSBlob->GetBufferSize(), &g_pVertexLayout);



	pVSBlob->Release();

	return g_pVertexLayout;
}

HRESULT Technique::setPixelShader(LPCWSTR filename, LPCSTR entryPoint, LPCSTR shaderModel, ID3D11Device* g_pd3dDevice){

	HRESULT hr = S_OK;

	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
	// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
	// Setting this flag improves the shader debugging experience, but still allows 
	// the shaders to be optimized and to run exactly the way they will run in 
	// the release configuration of this program.
	dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

	ID3DBlob* pPSBlob = nullptr;
	ID3DBlob* pErrorBlob = nullptr;
	hr = D3DCompileFromFile(filename, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, entryPoint, shaderModel,
		dwShaderFlags, 0, &pPSBlob, &pErrorBlob);
	if (FAILED(hr))
	{
		if (pErrorBlob)
		{
			std::ofstream fout("Shader_Debug.txt");
			fout << reinterpret_cast<const char*>(pErrorBlob->GetBufferPointer());
			OutputDebugStringA(reinterpret_cast<const char*>(pErrorBlob->GetBufferPointer()));
			pErrorBlob->Release();
		}

	}
	if (pErrorBlob) pErrorBlob->Release();

	hr = g_pd3dDevice->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr, &g_pPixelShader);
	if (FAILED(hr))
	{
		pPSBlob->Release();

	}

	pPSBlob->Release();
	return hr;
}

HRESULT Technique::setDomainShader(LPCWSTR filename, LPCSTR entryPoint, LPCSTR shaderModel, ID3D11Device* g_pd3dDevice){
	HRESULT hr = S_OK;

	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
	// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
	// Setting this flag improves the shader debugging experience, but still allows 
	// the shaders to be optimized and to run exactly the way they will run in 
	// the release configuration of this program.
	dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

	ID3DBlob* pDSBlob = nullptr;
	ID3DBlob* pErrorBlob = nullptr;
	hr = D3DCompileFromFile(filename, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, entryPoint, shaderModel,
		dwShaderFlags, 0, &pDSBlob, &pErrorBlob);
	if (FAILED(hr))
	{
		if (pErrorBlob)
		{
			std::ofstream fout("Shader_Debug.txt");
			fout << reinterpret_cast<const char*>(pErrorBlob->GetBufferPointer());
			OutputDebugStringA(reinterpret_cast<const char*>(pErrorBlob->GetBufferPointer()));
			pErrorBlob->Release();
		}

	}
	if (pErrorBlob) pErrorBlob->Release();

	hr = g_pd3dDevice->CreateDomainShader(pDSBlob->GetBufferPointer(), pDSBlob->GetBufferSize(), nullptr, &g_pDomainShader);
	if (FAILED(hr))
	{
		pDSBlob->Release();

	}

	pDSBlob->Release();
	return hr;
}

HRESULT Technique::setHullShader(LPCWSTR filename, LPCSTR entryPoint, LPCSTR shaderModel, ID3D11Device* g_pd3dDevice){
	HRESULT hr = S_OK;

	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
	// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
	// Setting this flag improves the shader debugging experience, but still allows 
	// the shaders to be optimized and to run exactly the way they will run in 
	// the release configuration of this program.
	dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

	ID3DBlob* pHSBlob = nullptr;
	ID3DBlob* pErrorBlob = nullptr;
	hr = D3DCompileFromFile(filename, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, entryPoint, shaderModel,
		dwShaderFlags, 0, &pHSBlob, &pErrorBlob);
	if (FAILED(hr))
	{
		if (pErrorBlob)
		{
			std::ofstream fout("Shader_Debug.txt");
			fout << reinterpret_cast<const char*>(pErrorBlob->GetBufferPointer());
			OutputDebugStringA(reinterpret_cast<const char*>(pErrorBlob->GetBufferPointer()));
			pErrorBlob->Release();
		}

	}
	if (pErrorBlob) pErrorBlob->Release();

	hr = g_pd3dDevice->CreateHullShader(pHSBlob->GetBufferPointer(), pHSBlob->GetBufferSize(), nullptr, &g_pHullShader);
	if (FAILED(hr))
	{
		pHSBlob->Release();

	}

	pHSBlob->Release();

	return hr;
}

HRESULT Technique::setComputeShader(LPCWSTR filename, LPCSTR entryPoint, LPCSTR shaderModel, ID3D11Device* g_pd3dDevice){
	HRESULT hr = S_OK;

	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
	// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
	// Setting this flag improves the shader debugging experience, but still allows 
	// the shaders to be optimized and to run exactly the way they will run in 
	// the release configuration of this program.
	dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

	ID3DBlob* pCSBlob = nullptr;
	ID3DBlob* pErrorBlob = nullptr;
	hr = D3DCompileFromFile(filename, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, entryPoint, shaderModel,
		dwShaderFlags, 0, &pCSBlob, &pErrorBlob);
	if (FAILED(hr))
	{
		if (pErrorBlob)
		{
			std::ofstream fout("Shader_Debug.txt");
			fout << reinterpret_cast<const char*>(pErrorBlob->GetBufferPointer());
			OutputDebugStringA(reinterpret_cast<const char*>(pErrorBlob->GetBufferPointer()));
			pErrorBlob->Release();
		}

	}
	if (pErrorBlob) pErrorBlob->Release();

	hr = g_pd3dDevice->CreateComputeShader(pCSBlob->GetBufferPointer(), pCSBlob->GetBufferSize(), nullptr, &g_pComputeShader);
	if (FAILED(hr))
	{
		pCSBlob->Release();

	}

	pCSBlob->Release();
	return hr;
}

void Technique::operator=(const Technique& tech2){
	if (g_pVertexShader != nullptr)
		g_pVertexShader->Release();

	if (g_pPixelShader != nullptr)
		g_pPixelShader->Release();

	if (g_pHullShader != nullptr)
		g_pHullShader->Release();
	
	if (g_pDomainShader != nullptr)
		g_pDomainShader->Release();
	
	if (g_pComputeShader != nullptr)
		g_pComputeShader->Release();

	this->g_pVertexShader = tech2.g_pVertexShader;
	this->g_pPixelShader = tech2.g_pPixelShader;
	this->g_pHullShader = tech2.g_pHullShader;
	this->g_pDomainShader = tech2.g_pDomainShader;
	this->g_pComputeShader = tech2.g_pComputeShader;
}
#ifndef D3D_INITIALIZER_H
#define D3D_INITIALIZER_H

#include <d3d11_1.h>
#include <directxcolors.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>
#include <winnt.h>
#include "VertexTypes.h"
#include "LightTypes.h"

struct SimpleVertex
{
	DirectX::XMFLOAT3 Pos;
	DirectX::XMFLOAT4 Color;
};


struct ConstantBuffer
{
	DirectX::XMMATRIX mWorld;
	DirectX::XMMATRIX mView;
	DirectX::XMMATRIX mProjection;
};




class D3DInitializer{

public:
	HWND                    g_hWnd = nullptr;
	D3D_DRIVER_TYPE         g_driverType = D3D_DRIVER_TYPE_NULL;
	ID3D11Device*           g_pd3dDevice = nullptr;
	IDXGISwapChain*         g_pSwapChain = nullptr;
	D3D_FEATURE_LEVEL       g_featureLevel = D3D_FEATURE_LEVEL_11_0;
	ID3D11DeviceContext*    g_pImmediateContext = nullptr;
	ID3D11Device1*          g_pd3dDevice1 = nullptr;
	ID3D11DeviceContext1*   g_pImmediateContext1 = nullptr;
	ID3D11RenderTargetView* g_pRenderTargetView = nullptr;
	ID3D11Texture2D*        g_pDepthStencil = nullptr;

	UINT width = 0;
	UINT height = 0;

	ID3D11Buffer* g_pVertexBuffer = nullptr;
	ID3D11Buffer* g_pIndexBuffer = nullptr;	

	//ToshRenderer* mToshRenderer = nullptr;

	ID3D11Buffer* g_pConstantBuffer = nullptr;
	

	DirectX::XMFLOAT4X4 g_World1;
	DirectX::XMFLOAT4X4 g_World2;
	DirectX::XMFLOAT4X4 g_View;
	DirectX::XMFLOAT4X4 g_Projection;

	ID3D11DepthStencilView* g_pDepthStencilView = nullptr;
	
	VertexTypes::VertexBasic* vertices = nullptr;
	UINT numVertices = 0;
	
	USHORT* indices = nullptr;



	D3DInitializer(HWND mWindowHandle);
	~D3DInitializer();

	HRESULT InitializeDevice();

	

	
	void setInputLayout(ID3D11InputLayout* g_pVertexLayout);

	HRESULT CreateVertexBuffer(DirectX::XMFLOAT3 p1, DirectX::XMFLOAT3 p2, DirectX::XMFLOAT3 p3, DirectX::XMFLOAT4 c1, DirectX::XMFLOAT4 c2, DirectX::XMFLOAT4 c3);
	HRESULT CreateVertexBuffer(int numVertices);
	HRESULT AddVertexPosition(DirectX::XMFLOAT3 position);
	HRESULT AddVertexColor(DirectX::XMFLOAT4 color);

	void populateIndex(WORD indices[], UINT numIndices);
	HRESULT CreateIndexBuffer(USHORT numIndices);
	void SetIndexBuffer();

	void SetVertexBuffer();
	void SetPrimitiveTopology();

	void ClearVertices();

	

	void SetVertexShader(ID3D11VertexShader* g_pVertexShader);
	void SetPixelShader(ID3D11PixelShader* g_pPixelShader);
	void SetHullShader(ID3D11HullShader* g_pHullShader);
	void SetDomainShader(ID3D11DomainShader* g_pDomainShader);
	

	void releaseBlob(ID3DBlob* blob);

	HRESULT CreateConstantBuffer();

	void InitializeWorldMatrix();
	void InitializeViewMatrix(float x, float y, float z);
	void InitializeProjectionMatrix();

	HRESULT CreateDepthStencilView();


	/*void setRenderer(ToshRenderer* tRend){
		mToshRenderer = tRend;
	}*/
};

#endif
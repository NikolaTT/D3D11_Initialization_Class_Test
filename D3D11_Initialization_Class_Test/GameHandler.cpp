#include "GameHandler.h"


GameHandler::GameHandler(HINSTANCE hInstance, int nCmdShow){
	
	//Initialize public members
	mWinInit = new WindowInitializer(hInstance, nCmdShow);
	mD3DInit = new D3DInitializer(mWinInit->g_hWnd);
	mTRenderer = new ToshRenderer(mD3DInit);
	RenderStates* mTRenderStates = new RenderStates();
	mTRenderStates->InitAll(mD3DInit->g_pd3dDevice);
	basicLevel = new BasicLevel("level1.txt");
	basicLevel->setInitializer(mD3DInit);



	//Copied from main
	mD3DInit->CreateDepthStencilView();

	mD3DInit->CompileShaderFromFile(L"OpaqueVS.hlsl", "VS", "vs_4_0", &(mD3DInit->pVSBlob));

	mD3DInit->CreateVertexShader(mD3DInit->pVSBlob->GetBufferPointer(), mD3DInit->pVSBlob->GetBufferSize(), nullptr, &(mD3DInit->g_pVertexShader));

	mD3DInit->AddInputLayout("POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0);

	mD3DInit->AddInputLayout("NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0);

	mD3DInit->AddInputLayout("TEXTURE", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 28, D3D11_INPUT_PER_VERTEX_DATA, 0);

	mD3DInit->AddInputLayout("TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 36, D3D11_INPUT_PER_VERTEX_DATA, 0);

	mD3DInit->AddInputLayout("DIS_TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 48, D3D11_INPUT_PER_VERTEX_DATA, 0);

	mD3DInit->CreateInputLayout(mD3DInit->layout->mTlayout, mD3DInit->layout->numElements, mD3DInit->pVSBlob->GetBufferPointer(),
		mD3DInit->pVSBlob->GetBufferSize(), &(mD3DInit->g_pVertexLayout));

	mD3DInit->setInputLayout();

	mD3DInit->CompileShaderFromFile(L"OpaquePS.hlsl", "PS", "ps_4_0", &(mD3DInit->pPSBlob));

	mD3DInit->CreatePixelShader(mD3DInit->pPSBlob->GetBufferPointer(), mD3DInit->pPSBlob->GetBufferSize(), nullptr,
		&mD3DInit->g_pPixelShader);

	mD3DInit->CompileShaderFromFile(L"OpaqueHS.hlsl", "HS", "hs_5_0", &(mD3DInit->pHSBlob));

	mD3DInit->CreateHullShader(mD3DInit->pHSBlob->GetBufferPointer(), mD3DInit->pHSBlob->GetBufferSize(), nullptr,
		&mD3DInit->g_pHullShader);

	mD3DInit->CompileShaderFromFile(L"OpaqueDS.hlsl", "DS", "ds_5_0", &(mD3DInit->pDSBlob));

	mD3DInit->CreateDomainShader(mD3DInit->pDSBlob->GetBufferPointer(), mD3DInit->pDSBlob->GetBufferSize(), nullptr,
		&mD3DInit->g_pDomainShader);

	mD3DInit->InitializeWorldMatrix();

	mD3DInit->InitializeViewMatrix(12.5f, 2.5f, 3.5f);

	mD3DInit->InitializeProjectionMatrix();



	//AlphaBlendSorter alphaBlendSorter;
	//alphaBlendSorter.sortVertices(basicLevel->vertices, mD3DInit->g_World1, mD3DInit->g_View, mD3DInit->g_Projection);

	//numVertices = geometryVector[0].vertices.size();

	//mD3DInit->vertices = new VertexTypes::VertexBasic[geometryVector[0].vertices.size()];


	mD3DInit->vertices = new VertexTypes::VertexBasic[basicLevel->vertices.size()];
	basicLevel->setVertices();


	/*for (int i = 0; i < basicLevel->vertices.size(); i++){

	mD3DInit->vertices[i] = geometryVector[0].vertices[i];

	/*mD3DInit->vertices[i].Pos.x = rand() / (float)RAND_MAX;
	mD3DInit->vertices[i].Pos.y = rand() / (float)RAND_MAX;
	mD3DInit->vertices[i].Pos.z = rand() / (float)RAND_MAX;*/
	//}

	mD3DInit->CreateVertexBuffer(basicLevel->vertices.size());

	mD3DInit->SetVertexBuffer();

	mD3DInit->SetPrimitiveTopology();

	mD3DInit->CreateConstantBuffer();

	mD3DInit->SetVertexShader();

	mD3DInit->SetPixelShader();

	mD3DInit->SetHullShader();

	mD3DInit->SetDomainShader();

	mTRenderer->CreateCBPerFrame();
	mTRenderer->CreateCBPerObject();
	mTRenderer->CreateShaderRV(L"DisplacementMap3.DDS", &mTRenderer->g_pDisplacementTextureRV);
	mTRenderer->CreateShaderRV(L"WireFence.dds", &mTRenderer->g_pTextureRV);
	mTRenderer->CreateCubeMapShaderRV(L"desertcube1024.dds");
}


void GameHandler::update(){

}




void GameHandler::render(){

}
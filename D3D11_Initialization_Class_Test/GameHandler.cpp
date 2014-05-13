#include "GameHandler.h"
#include <DirectXMath.h>

using namespace DirectX;

GameHandler::GameHandler(HINSTANCE hInstance, int nCmdShow){

	//Initialize public members
	mWinInit = new WindowInitializer(hInstance, nCmdShow);
	mD3DInitializer = new D3DInitializer(mWinInit->g_hWnd);
	mTRenderer = new ToshRenderer(mD3DInitializer);
	RenderStates* mTRenderStates = new RenderStates();
	mTRenderStates->InitAll(mD3DInitializer->g_pd3dDevice);
	basicLevel = new BasicLevel("level1.txt");
	basicLevel->setInitializer(mD3DInitializer);
	blendFactor[0] = 0.0f;
	blendFactor[1] = 0.0f;
	blendFactor[2] = 0.0f;
	blendFactor[3] = 0.0f;



	//Copied from main
	mD3DInitializer->CreateDepthStencilView();

	mD3DInitializer->CompileShaderFromFile(L"OpaqueVS.hlsl", "VS", "vs_4_0", &(mD3DInitializer->pVSBlob));

	mD3DInitializer->CreateVertexShader(mD3DInitializer->pVSBlob->GetBufferPointer(), mD3DInitializer->pVSBlob->GetBufferSize(), nullptr, &(mD3DInitializer->g_pVertexShader));

	mD3DInitializer->AddInputLayout("POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0);

	mD3DInitializer->AddInputLayout("NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0);

	mD3DInitializer->AddInputLayout("TEXTURE", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 28, D3D11_INPUT_PER_VERTEX_DATA, 0);

	mD3DInitializer->AddInputLayout("TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 36, D3D11_INPUT_PER_VERTEX_DATA, 0);

	mD3DInitializer->AddInputLayout("DIS_TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 48, D3D11_INPUT_PER_VERTEX_DATA, 0);

	mD3DInitializer->CreateInputLayout(mD3DInitializer->layout->mTlayout, mD3DInitializer->layout->numElements, mD3DInitializer->pVSBlob->GetBufferPointer(),
		mD3DInitializer->pVSBlob->GetBufferSize(), &(mD3DInitializer->g_pVertexLayout));

	mD3DInitializer->setInputLayout();

	mD3DInitializer->CompileShaderFromFile(L"OpaquePS.hlsl", "PS", "ps_4_0", &(mD3DInitializer->pPSBlob));

	mD3DInitializer->CreatePixelShader(mD3DInitializer->pPSBlob->GetBufferPointer(), mD3DInitializer->pPSBlob->GetBufferSize(), nullptr,
		&mD3DInitializer->g_pPixelShader);

	mD3DInitializer->CompileShaderFromFile(L"OpaqueHS.hlsl", "HS", "hs_5_0", &(mD3DInitializer->pHSBlob));

	mD3DInitializer->CreateHullShader(mD3DInitializer->pHSBlob->GetBufferPointer(), mD3DInitializer->pHSBlob->GetBufferSize(), nullptr,
		&mD3DInitializer->g_pHullShader);

	mD3DInitializer->CompileShaderFromFile(L"OpaqueDS.hlsl", "DS", "ds_5_0", &(mD3DInitializer->pDSBlob));

	mD3DInitializer->CreateDomainShader(mD3DInitializer->pDSBlob->GetBufferPointer(), mD3DInitializer->pDSBlob->GetBufferSize(), nullptr,
		&mD3DInitializer->g_pDomainShader);

	mD3DInitializer->InitializeWorldMatrix();

	mD3DInitializer->InitializeViewMatrix(12.5f, 12.5f, 13.5f);

	mD3DInitializer->InitializeProjectionMatrix();



	//AlphaBlendSorter alphaBlendSorter;
	//alphaBlendSorter.sortVertices(basicLevel->vertices, mD3DInitializer->g_World1, mD3DInitializer->g_View, mD3DInitializer->g_Projection);

	//numVertices = geometryVector[0].vertices.size();

	//mD3DInitializer->vertices = new VertexTypes::VertexBasic[geometryVector[0].vertices.size()];


	mD3DInitializer->vertices = new VertexTypes::VertexBasic[basicLevel->vertices.size()];
	basicLevel->setVertices();


	/*for (int i = 0; i < basicLevel->vertices.size(); i++){

	mD3DInitializer->vertices[i] = geometryVector[0].vertices[i];

	/*mD3DInitializer->vertices[i].Pos.x = rand() / (float)RAND_MAX;
	mD3DInitializer->vertices[i].Pos.y = rand() / (float)RAND_MAX;
	mD3DInitializer->vertices[i].Pos.z = rand() / (float)RAND_MAX;*/
	//}

	mD3DInitializer->CreateVertexBuffer(basicLevel->vertices.size());

	mD3DInitializer->SetVertexBuffer();

	mD3DInitializer->SetPrimitiveTopology();

	mD3DInitializer->CreateConstantBuffer();

	mD3DInitializer->SetVertexShader();

	mD3DInitializer->SetPixelShader();

	mD3DInitializer->SetHullShader();

	mD3DInitializer->SetDomainShader();

	mTRenderer->CreateCBPerFrame();
	mTRenderer->CreateCBPerObject();
	mTRenderer->CreateShaderRV(L"DisplacementMap3.DDS", &mTRenderer->g_pDisplacementTextureRV);
	mTRenderer->CreateShaderRV(L"WireFence.dds", &mTRenderer->g_pTextureRV);
	mTRenderer->CreateCubeMapShaderRV(L"desertcube1024.dds");
}


void GameHandler::update(){

}




void GameHandler::render(){

	// Now set the rasterizer state and blend state.
	// Blend factor global constant hardcoded

	mD3DInitializer->g_pImmediateContext->RSSetState(mTRenderStates->TutorialRS);
	//mD3DInitializer->g_pImmediateContext->OMSetBlendState(mTRenderStates->TransparentBS, blendFactor, 0xffffffff);
	//mD3DInitializer->g_pImmediateContext->OMSetDepthStencilState(mTRenderStates->TutorialDDS, 1.0f);




	//
	// Clear the back buffer
	//
	mD3DInitializer->g_pImmediateContext->ClearRenderTargetView(mD3DInitializer->g_pRenderTargetView, DirectX::Colors::White);

	//
	// Clear the depth buffer to 1.0 (max depth)
	//
	mD3DInitializer->g_pImmediateContext->ClearDepthStencilView(mD3DInitializer->g_pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
		1.0f, 0);

	ConstantBuffer cb1;
	cb1.mWorld = XMMatrixTranspose(DirectX::XMLoadFloat4x4(&mD3DInitializer->g_World1));
	cb1.mView = XMMatrixTranspose(DirectX::XMLoadFloat4x4(&mD3DInitializer->g_View));
	cb1.mProjection = XMMatrixTranspose(DirectX::XMLoadFloat4x4(&mD3DInitializer->g_Projection));
	mD3DInitializer->g_pImmediateContext->UpdateSubresource(mD3DInitializer->g_pConstantBuffer, 0, nullptr, &cb1, 0, 0);

	cbPerFrame v_cbPerFrame;
	cbPerObject v_cbPerObject;


	//Set Per Frame Constant Buffer

	v_cbPerFrame.gDirLight = mTRenderer->mDirLight;
	v_cbPerFrame.gEyePosW = DirectX::XMFLOAT3(12.5f, 2.5f, 3.5f);
	v_cbPerFrame.gPointLight = mTRenderer->mPointLight;
	v_cbPerFrame.gSpotLight = mTRenderer->mSpotLight;
	v_cbPerFrame.gPointLight.Position.x = 0.0f;//70.0f*cosf(0.02f*rotatePointLightAngle);
	v_cbPerFrame.gPointLight.Position.z = 20.5f;//70.0f*sinf(0.02f*rotatePointLightAngle);
	v_cbPerFrame.gPointLight.Position.y = 1.5f;


	//Comment out point light rotation
	XMVECTOR gPointLightPos = XMLoadFloat3(&v_cbPerFrame.gPointLight.Position);
	gPointLightPos = XMVector3Transform(gPointLightPos, XMMatrixRotationY(-rotatePointLightAngle));
	XMStoreFloat3(&v_cbPerFrame.gPointLight.Position, gPointLightPos);
	//v_cbPerFrame.gPointLight.Position.y += 10;

	rotatePointLightAngle += 0.0001;

	

	//Set Per Object Constant Buffer
	v_cbPerObject.gMaterial = mTRenderer->CubeMat;

	//DirectX::XMStoreFloat4x4(&mD3DInitializer->g_World1, XMMatrixRotationY(rotatePointLightAngle));

	v_cbPerObject.gWorld = XMMatrixTranspose(DirectX::XMLoadFloat4x4(&mD3DInitializer->g_World1));

	//Not true to original
	DirectX::XMVECTOR det = XMMatrixDeterminant(v_cbPerObject.gWorld);
	v_cbPerObject.gWorldInvTranspose = XMMatrixInverse(&det, v_cbPerObject.gWorld);
	v_cbPerObject.gWorldInvTranspose = XMMatrixTranspose(v_cbPerObject.gWorldInvTranspose);

	v_cbPerObject.gWorldViewProj = XMMatrixTranspose(DirectX::XMLoadFloat4x4(&mD3DInitializer->g_World1)
		* DirectX::XMLoadFloat4x4(&mD3DInitializer->g_View)
		* DirectX::XMLoadFloat4x4(&mD3DInitializer->g_Projection));
	v_cbPerObject.gTexTransform = DirectX::XMMatrixIdentity();
	v_cbPerObject.gViewProj = XMMatrixTranspose(DirectX::XMLoadFloat4x4(&mD3DInitializer->g_View)
		* DirectX::XMLoadFloat4x4(&mD3DInitializer->g_Projection));

	//
	//End Constant Buffer Initialization
	//


	//Set VS Constant Buffer
	mD3DInitializer->g_pImmediateContext->UpdateSubresource(mTRenderer->g_pcbPerFrame, 0, nullptr, &v_cbPerFrame, 0, 0);
	mD3DInitializer->g_pImmediateContext->VSSetConstantBuffers(1, 1, &mTRenderer->g_pcbPerFrame);

	mD3DInitializer->g_pImmediateContext->UpdateSubresource(mTRenderer->g_pcbPerObject, 0, nullptr, &v_cbPerObject, 0, 0);
	mD3DInitializer->g_pImmediateContext->VSSetConstantBuffers(2, 1, &mTRenderer->g_pcbPerObject);



	//Set PS Constant Buffer
	mD3DInitializer->g_pImmediateContext->UpdateSubresource(mTRenderer->g_pcbPerFrame, 0, nullptr, &v_cbPerFrame, 0, 0);
	mD3DInitializer->g_pImmediateContext->PSSetConstantBuffers(1, 1, &mTRenderer->g_pcbPerFrame);

	mD3DInitializer->g_pImmediateContext->UpdateSubresource(mTRenderer->g_pcbPerObject, 0, nullptr, &v_cbPerObject, 0, 0);
	mD3DInitializer->g_pImmediateContext->PSSetConstantBuffers(2, 1, &mTRenderer->g_pcbPerObject);

	//Set PS Texture

	mD3DInitializer->g_pImmediateContext->PSSetShaderResources(0, 1, &mTRenderer->g_pCubeMapRV);
	mD3DInitializer->g_pImmediateContext->PSSetShaderResources(1, 1, &mTRenderer->g_pTextureRV);



	//mD3DInitializer->g_pImmediateContext->VSSetConstantBuffers(0, 1, &mD3DInitializer->g_pConstantBuffer);
	//mD3DInitializer->g_pImmediateContext->HSSetConstantBuffers(0, 1, &mD3DInitializer->g_pConstantBuffer);
	//mD3DInitializer->g_pImmediateContext->DSSetConstantBuffers(0, 1, &mD3DInitializer->g_pConstantBuffer);




	//Set DS Constant Buffer
	mD3DInitializer->g_pImmediateContext->UpdateSubresource(mTRenderer->g_pcbPerFrame, 0, nullptr, &v_cbPerFrame, 0, 0);
	mD3DInitializer->g_pImmediateContext->DSSetConstantBuffers(1, 1, &mTRenderer->g_pcbPerFrame);

	mD3DInitializer->g_pImmediateContext->UpdateSubresource(mTRenderer->g_pcbPerObject, 0, nullptr, &v_cbPerObject, 0, 0);
	mD3DInitializer->g_pImmediateContext->DSSetConstantBuffers(2, 1, &mTRenderer->g_pcbPerObject);

	//Set DS Texture

	mD3DInitializer->g_pImmediateContext->DSSetShaderResources(0, 1, &mTRenderer->g_pDisplacementTextureRV);


	//draw cube to both depth and stencil buffer as normal
	mD3DInitializer->g_pImmediateContext->Draw(basicLevel->levelGeometryVector[0].vertices.size(), 0);

	//now draw mirror to stencil buffer only
	//do not draw to render target
	mD3DInitializer->g_pImmediateContext->OMSetBlendState(RenderStates::NoRenderTargetWritesBS, blendFactor, 0xffffffff);

	// Render visible mirror pixels to stencil buffer.
	// Do not write mirror depth to depth buffer at this point, otherwise it will occlude the reflection.
	mD3DInitializer->g_pImmediateContext->OMSetDepthStencilState(RenderStates::MarkMirrorDSS, 1);

	//levelGeometryVector[1] is Mirror, [0] is Cube; Makes assumptions.
	mD3DInitializer->g_pImmediateContext->Draw(basicLevel->levelGeometryVector[1].vertices.size(),
		basicLevel->levelGeometryVector[0].vertices.size());

	// Restore states.
	mD3DInitializer->g_pImmediateContext->OMSetDepthStencilState(0, 0);
	mD3DInitializer->g_pImmediateContext->OMSetBlendState(0, blendFactor, 0xffffffff);

	//
	// Draw the cube reflection.
	//


	XMVECTOR mirrorPlane = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f); // xy plane
	XMMATRIX R = XMMatrixReflect(mirrorPlane);
	XMMATRIX world = R;
	XMMATRIX worldInvTranspose = DirectX::XMMatrixInverse(&DirectX::XMMatrixDeterminant(world), DirectX::XMMatrixTranspose(world));
	XMMATRIX worldViewProj = world *
		DirectX::XMLoadFloat4x4(&mD3DInitializer->g_View) *
		DirectX::XMLoadFloat4x4(&mD3DInitializer->g_Projection);


	// Cache the old light directions, and reflect the light directions.
	// Not using directional lights so code under is commented.
	/*XMFLOAT3 oldLightDirections[3];
	for (int i = 0; i < 3; ++i)
	{
	oldLightDirections[i] = mDirLights[i].Direction;

	XMVECTOR lightDir = XMLoadFloat3(&mDirLights[i].Direction);
	XMVECTOR reflectedLightDir = XMVector3TransformNormal(lightDir, R);
	XMStoreFloat3(&mDirLights[i].Direction, reflectedLightDir);
	}*/

	//
	//Still need  to mirror point light though.
	//

	// Cull clockwise triangles for reflection.
	mD3DInitializer->g_pImmediateContext->RSSetState(RenderStates::CullClockwiseRS);

	// Only draw reflection into visible mirror pixels as marked by the stencil buffer. 
	mD3DInitializer->g_pImmediateContext->OMSetDepthStencilState(RenderStates::DrawReflectionDSS, 1);

	mD3DInitializer->g_pImmediateContext->Draw(basicLevel->levelGeometryVector[0].vertices.size(), 0);

	// Restore default states.
	mD3DInitializer->g_pImmediateContext->RSSetState(0);
	mD3DInitializer->g_pImmediateContext->OMSetDepthStencilState(0, 0);

	// Not using directional lights so code under is commented.
	// Restore light directions.
	/*for (int i = 0; i < 3; ++i)
	{
	mDirLights[i].Direction = oldLightDirections[i];
	}*/




	//
	// Draw the mirror to the back buffer as usual but with transparency
	// blending so the reflection shows through.
	// 

	// Set per object constants.
	world = XMMatrixIdentity();
	worldInvTranspose = XMMatrixInverse(&XMMatrixDeterminant(world), XMMatrixTranspose(world));
	worldViewProj = world *
		DirectX::XMLoadFloat4x4(&mD3DInitializer->g_View) *
		DirectX::XMLoadFloat4x4(&mD3DInitializer->g_Projection);

	// Mirror
	mD3DInitializer->g_pImmediateContext->OMSetBlendState(RenderStates::TransparentBS, blendFactor, 0xffffffff);
	mD3DInitializer->g_pImmediateContext->Draw(basicLevel->levelGeometryVector[1].vertices.size(),
		basicLevel->levelGeometryVector[0].vertices.size());

	// Light position

	v_cbPerObject.gWorld = XMMatrixTranspose(XMMatrixTranslation(v_cbPerFrame.gPointLight.Position.x, v_cbPerFrame.gPointLight.Position.y,
		v_cbPerFrame.gPointLight.Position.z));
	//Not true to original
	det = XMMatrixDeterminant(v_cbPerObject.gWorld);
	v_cbPerObject.gWorldInvTranspose = XMMatrixInverse(&det, v_cbPerObject.gWorld);
	v_cbPerObject.gWorldInvTranspose = XMMatrixTranspose(v_cbPerObject.gWorldInvTranspose);

	v_cbPerObject.gWorldViewProj = XMMatrixTranspose(DirectX::XMLoadFloat4x4(&mD3DInitializer->g_World1)
		* DirectX::XMLoadFloat4x4(&mD3DInitializer->g_View)
		* DirectX::XMLoadFloat4x4(&mD3DInitializer->g_Projection));
	v_cbPerObject.gTexTransform = DirectX::XMMatrixIdentity();
	v_cbPerObject.gViewProj = XMMatrixTranspose(DirectX::XMLoadFloat4x4(&mD3DInitializer->g_View)
		* DirectX::XMLoadFloat4x4(&mD3DInitializer->g_Projection));

	//
	//End Constant Buffer Initialization
	//


	//Set VS Constant Buffer
	mD3DInitializer->g_pImmediateContext->UpdateSubresource(mTRenderer->g_pcbPerFrame, 0, nullptr, &v_cbPerFrame, 0, 0);
	mD3DInitializer->g_pImmediateContext->VSSetConstantBuffers(1, 1, &mTRenderer->g_pcbPerFrame);

	mD3DInitializer->g_pImmediateContext->UpdateSubresource(mTRenderer->g_pcbPerObject, 0, nullptr, &v_cbPerObject, 0, 0);
	mD3DInitializer->g_pImmediateContext->VSSetConstantBuffers(2, 1, &mTRenderer->g_pcbPerObject);



	//Set PS Constant Buffer
	mD3DInitializer->g_pImmediateContext->UpdateSubresource(mTRenderer->g_pcbPerFrame, 0, nullptr, &v_cbPerFrame, 0, 0);
	mD3DInitializer->g_pImmediateContext->PSSetConstantBuffers(1, 1, &mTRenderer->g_pcbPerFrame);

	mD3DInitializer->g_pImmediateContext->UpdateSubresource(mTRenderer->g_pcbPerObject, 0, nullptr, &v_cbPerObject, 0, 0);
	mD3DInitializer->g_pImmediateContext->PSSetConstantBuffers(2, 1, &mTRenderer->g_pcbPerObject);

	//Set PS Texture

	mD3DInitializer->g_pImmediateContext->PSSetShaderResources(0, 1, &mTRenderer->g_pCubeMapRV);
	mD3DInitializer->g_pImmediateContext->PSSetShaderResources(1, 1, &mTRenderer->g_pTextureRV);



	//mD3DInitializer->g_pImmediateContext->VSSetConstantBuffers(0, 1, &mD3DInitializer->g_pConstantBuffer);
	//mD3DInitializer->g_pImmediateContext->HSSetConstantBuffers(0, 1, &mD3DInitializer->g_pConstantBuffer);
	//mD3DInitializer->g_pImmediateContext->DSSetConstantBuffers(0, 1, &mD3DInitializer->g_pConstantBuffer);




	//Set DS Constant Buffer
	mD3DInitializer->g_pImmediateContext->UpdateSubresource(mTRenderer->g_pcbPerFrame, 0, nullptr, &v_cbPerFrame, 0, 0);
	mD3DInitializer->g_pImmediateContext->DSSetConstantBuffers(1, 1, &mTRenderer->g_pcbPerFrame);

	mD3DInitializer->g_pImmediateContext->UpdateSubresource(mTRenderer->g_pcbPerObject, 0, nullptr, &v_cbPerObject, 0, 0);
	mD3DInitializer->g_pImmediateContext->DSSetConstantBuffers(2, 1, &mTRenderer->g_pcbPerObject);

	//Set DS Texture

	mD3DInitializer->g_pImmediateContext->DSSetShaderResources(0, 1, &mTRenderer->g_pDisplacementTextureRV);

	mD3DInitializer->g_pImmediateContext->Draw(basicLevel->levelGeometryVector[2].vertices.size(),
		basicLevel->levelGeometryVector[0].vertices.size() + basicLevel->levelGeometryVector[1].vertices.size());


	mD3DInitializer->g_pSwapChain->Present(0, 0);


}
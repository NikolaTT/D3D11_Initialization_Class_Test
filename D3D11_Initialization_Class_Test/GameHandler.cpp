#include "GameHandler.h"
#include "TechniqueLoader.h"
#include <DirectXMath.h>
#include <iostream>


using namespace DirectX; using namespace std;

GameHandler::GameHandler(HINSTANCE hInstance, int nCmdShow){

	//Initialize public members
	mWinInit = new WindowInitializer(hInstance, nCmdShow);
	mD3DInitializer = new D3DInitializer(mWinInit->g_hWnd);
	mTRenderer = new ToshRenderer(mD3DInitializer);
	RenderStates* mTRenderStates = new RenderStates();
	layouts = new InputLayoutDescription();
	mTRenderStates->InitAll(mD3DInitializer->g_pd3dDevice);
	basicLevel = new BasicLevel("level1.txt");
	basicLevel->setInitializer(mD3DInitializer);
	blendFactor[0] = 0.0f;
	blendFactor[1] = 0.0f;
	blendFactor[2] = 0.0f;
	blendFactor[3] = 0.0f;

	std::string techFile = "techniques.txt";
	TechniqueLoader techLoader(techFile, techniqueMap,
		mD3DInitializer->g_pd3dDevice, *layouts, g_pVertexLayoutMap);


	//Copied from main
	mD3DInitializer->CreateDepthStencilView();


	mD3DInitializer->InitializeWorldMatrix();

	mD3DInitializer->InitializeViewMatrix(4.5f, 3.0f, 6.5f);

	mD3DInitializer->InitializeProjectionMatrix();



	//AlphaBlendSorter alphaBlendSorter;
	//alphaBlendSorter.sortVertices(basicLevel->vertices, mD3DInitializer->g_World1, mD3DInitializer->g_View, mD3DInitializer->g_Projection);

	//numVertices = geometryVector[0].vertices.size();

	//mD3DInitializer->vertices = new VertexTypes::VertexBasic[geometryVector[0].vertices.size()];


	mD3DInitializer->vertices = new VertexTypes::VertexBasic[basicLevel->vertices.size()];
	basicLevel->setVertices();

	mD3DInitializer->indices = new USHORT[basicLevel->indices.size()];
	basicLevel->setIndices();


	/*for (int i = 0; i < basicLevel->vertices.size(); i++){

	mD3DInitializer->vertices[i] = geometryVector[0].vertices[i];

	/*mD3DInitializer->vertices[i].Pos.x = rand() / (float)RAND_MAX;
	mD3DInitializer->vertices[i].Pos.y = rand() / (float)RAND_MAX;
	mD3DInitializer->vertices[i].Pos.z = rand() / (float)RAND_MAX;*/
	//}

	mD3DInitializer->CreateVertexBuffer(basicLevel->vertices.size());
	mD3DInitializer->CreateIndexBuffer(basicLevel->indices.size());

	mD3DInitializer->SetVertexBuffer();
	mD3DInitializer->SetIndexBuffer();

	mD3DInitializer->g_pImmediateContext->IASetInputLayout(g_pVertexLayoutMap["Basic32"]);


	mD3DInitializer->SetPrimitiveTopology();

	mD3DInitializer->CreateConstantBuffer();

	mD3DInitializer->SetVertexShader(techniqueMap["opaque"].g_pVertexShader);

	mD3DInitializer->SetPixelShader(techniqueMap["opaque"].g_pPixelShader);

	mD3DInitializer->SetHullShader(techniqueMap["opaque"].g_pHullShader);

	mD3DInitializer->SetDomainShader(techniqueMap["opaque"].g_pDomainShader);

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

	rotatePointLightAngle = -0.20;
	rotatePointLightAngle += 0.00001;

	

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
	mD3DInitializer->g_pImmediateContext->DrawIndexed(basicLevel->levelGeometryVector[0].numIndices, 0, 0);
		
		//(basicLevel->levelGeometryVector[0].vertices.size(), 0);

	//now draw mirror to stencil buffer only
	//do not draw to render target
	mD3DInitializer->g_pImmediateContext->OMSetBlendState(RenderStates::NoRenderTargetWritesBS, blendFactor, 0xffffffff);

	// Render visible mirror pixels to stencil buffer.
	// Do not write mirror depth to depth buffer at this point, otherwise it will occlude the reflection.
	mD3DInitializer->g_pImmediateContext->OMSetDepthStencilState(RenderStates::MarkMirrorDSS, 1);

	//levelGeometryVector[1] is Mirror, [0] is Cube;
	mD3DInitializer->g_pImmediateContext->DrawIndexed(basicLevel->levelGeometryVector[1].numIndices,
		basicLevel->levelGeometryVector[0].numIndices, basicLevel->levelGeometryVector[0].vertices.size());

	// Restore states.
	mD3DInitializer->g_pImmediateContext->OMSetDepthStencilState(0, 0);
	mD3DInitializer->g_pImmediateContext->OMSetBlendState(0, blendFactor, 0xffffffff);

	//
	// Draw the cube reflection.
	//

	//create mirror matrix
	XMVECTOR mirrorPlane = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f); // xy plane
	XMMATRIX R = XMMatrixReflect(mirrorPlane);
	XMMATRIX world = XMMatrixIdentity() * R * XMMatrixTranslation(0.0f, 0.0f, -5.0f);
	XMMATRIX viewProj = DirectX::XMLoadFloat4x4(&mD3DInitializer->g_View) *
		DirectX::XMLoadFloat4x4(&mD3DInitializer->g_Projection);
	XMMATRIX worldInvTranspose = DirectX::XMMatrixInverse(&DirectX::XMMatrixDeterminant(world), DirectX::XMMatrixTranspose(world));
	XMMATRIX worldViewProj = world *
		DirectX::XMLoadFloat4x4(&mD3DInitializer->g_View) *
		DirectX::XMLoadFloat4x4(&mD3DInitializer->g_Projection);

	//update constant buffer
	v_cbPerObject.gWorld = XMMatrixTranspose(DirectX::XMLoadFloat4x4(&mD3DInitializer->g_World1) * R * XMMatrixTranslation(0.0f, 0.0f, -5.0f));
	det = XMMatrixDeterminant(v_cbPerObject.gWorld);
	v_cbPerObject.gWorldInvTranspose = XMMatrixInverse(&det, world);
	v_cbPerObject.gWorldInvTranspose = XMMatrixTranspose(v_cbPerObject.gWorldInvTranspose);

	v_cbPerObject.gWorldViewProj = XMMatrixTranspose(world
		* DirectX::XMLoadFloat4x4(&mD3DInitializer->g_View)
		* DirectX::XMLoadFloat4x4(&mD3DInitializer->g_Projection));
	v_cbPerObject.gTexTransform = DirectX::XMMatrixIdentity();
	v_cbPerObject.gViewProj = XMMatrixTranspose(DirectX::XMLoadFloat4x4(&mD3DInitializer->g_View)
		* DirectX::XMLoadFloat4x4(&mD3DInitializer->g_Projection));


	/*v_cbPerObject.gWorld = XMMatrixTranspose(world);
	v_cbPerObject.gWorldInvTranspose = worldInvTranspose;
	v_cbPerObject.gWorldViewProj = XMMatrixTranspose(worldViewProj);
	v_cbPerObject.gViewProj = XMMatrixTranspose(viewProj);*/
	
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

	//mD3DInitializer->g_pImmediateContext->DrawIndexed(basicLevel->levelGeometryVector[2].numIndices,
		//basicLevel->levelGeometryVector[0].numIndices + basicLevel->levelGeometryVector[1].numIndices,
		//basicLevel->levelGeometryVector[0].vertices.size() + basicLevel->levelGeometryVector[1].vertices.size());



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
	mD3DInitializer->g_pImmediateContext->RSSetState(RenderStates::NoCullRS);

	// Only draw reflection into visible mirror pixels as marked by the stencil buffer. 
	mD3DInitializer->g_pImmediateContext->OMSetDepthStencilState(RenderStates::DrawReflectionDSS, 1);

	mD3DInitializer->g_pImmediateContext->DrawIndexed(basicLevel->levelGeometryVector[0].numIndices, 0, 0);

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

	v_cbPerObject.gWorld = XMMatrixTranspose(DirectX::XMLoadFloat4x4(&mD3DInitializer->g_World1));

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

	// Mirror
	mD3DInitializer->g_pImmediateContext->OMSetBlendState(RenderStates::TransparentBS, blendFactor, 0xffffffff);
	mD3DInitializer->g_pImmediateContext->DrawIndexed(basicLevel->levelGeometryVector[1].numIndices,
		basicLevel->levelGeometryVector[0].numIndices, basicLevel->levelGeometryVector[0].vertices.size());

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

	/*mD3DInitializer->g_pImmediateContext->DrawIndexed(basicLevel->levelGeometryVector[2].numIndices,
		basicLevel->levelGeometryVector[0].numIndices + basicLevel->levelGeometryVector[1].numIndices, 
		basicLevel->levelGeometryVector[0].vertices.size() + basicLevel->levelGeometryVector[1].vertices.size());*/


	mD3DInitializer->g_pSwapChain->Present(0, 0);


}
// Game handler is responsible for keeping track of the created Window, 
// the DirectX device (context, swapchain, so on) as well as
// of the renderer and the current level

#include "D3DInitializer.h"
#include "ToshRenderer.h"
#include "WindowInitialization.h"
#include "RenderStates.h"
#include "Technique.h"
#include "BasicLevel.h"
#include <map>

class GameHandler{

public:
	WindowInitializer* mWinInit;
	D3DInitializer* mD3DInitializer;
	ToshRenderer* mTRenderer;
	RenderStates* mTRenderStates;
	BasicLevel* basicLevel;
	

	//map < shader name, map < model name, object position > >
	std::map<std::string, std::map<std::string, DirectX::XMMATRIX>> shaderModelObjectMap;
	
	float rotatePointLightAngle = 0.0f;
	float blendFactor[4];

	GameHandler();
	GameHandler(HINSTANCE hInstance, int nCmdShow);

	void update();
	void render();

};
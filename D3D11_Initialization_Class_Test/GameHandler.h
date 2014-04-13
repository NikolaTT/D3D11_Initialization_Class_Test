// Game handler is responsible for keeping track of the created Window, 
// the DirectX device (context, swapchain, so on) as well as
// of the renderer and the current level

#include "D3DInitializer.h"
#include "ToshRenderer.h"
#include "WindowInitialization.h"
#include "RenderStates.h"
#include "BasicLevel.h"

class GameHandler{

public:
	WindowInitializer* mWinInit;
	D3DInitializer* mD3DInitializer;
	ToshRenderer* mTRenderer;
	RenderStates* mTRenderStates;
	BasicLevel* basicLevel;
	
	
	float rotatePointLightAngle = 0.0f;
	float blendFactor[4];

	GameHandler();
	GameHandler(HINSTANCE hInstance, int nCmdShow);

	void update();
	void render();

};
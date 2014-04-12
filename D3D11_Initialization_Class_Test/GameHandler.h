// Game handler is responsible for keeping track of the created Window, 
// the DirectX device (context, swapchain, so on) as well as
// of the renderer and the current level

#include "D3DInitializer.h"
#include "ToshRenderer.h"
#include "WindowInitialization.h"



class GameHandler{

public:
	WindowInitializer* mWinInit;
	D3DInitializer* mD3DInit;
	ToshRenderer* mTRenderer;

	GameHandler();
	GameHandler(HINSTANCE hInstance, int nCmdShow);

};